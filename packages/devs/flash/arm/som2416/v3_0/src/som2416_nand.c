//====================================================================
// File Name : Nand.c
// Function  : S3C2443 8-bit interface Nand Test program
// Date      : May 22, 2006
// Version   : 0.0
// History
//   R0.0 (200305xx): Modified for 2440 from 2410. -> DonGo
//   R0.x (2005. 05. 20): Modified by Jcs
//====================================================================


/**************** K9s1208 NAND flash ********************/
// 1block=(512+16)bytes x 32pages
// 4096block
// Block: A[23:14], Page: [13:9]
/**************** K9K2G16 NAND flash *******************/
// 1block=(2048+64)bytes x 64pages
// 2048block
// Block: A[23:14], page: [13:9]
/*****************************************************/

#include <pkgconf/hal.h>
#include <cyg/hal/hal_arch.h>
#include <cyg/hal/hal_cache.h>
#include <cyg/infra/diag.h>

#include <cyg/hal/s3c2416.h>
#include <som2416_nand.h>

#if 1
  #define nand_printf diag_printf
#else
  #define nand_printf(arg,...) {}
#endif


#define BAD_CHECK	(1)
#define ECC_CHECK	(0)


volatile unsigned char NF8_Spare_Data[16];
volatile unsigned char Adv_NF8_Spare_Data[64];

		 
volatile unsigned int srcAddress;
volatile unsigned int targetBlock;	    // Block number (0 ~ 4095)
volatile unsigned int targetSize;	    // Total byte size 

volatile int NFConDone;

static unsigned char se8Buf[16]={
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff
};


static unsigned char Adv_se8Buf[64]={
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};



void NFCon_Int(void)
{
	
	 NFConDone=1;
	rINTMSK|=BIT_NFCON;
	ClearPending(BIT_NFCON);
	if(rNFSTAT&0x20)	nand_printf("Illegal Access is detected!!!\n");
}


//*************************************************

unsigned char Read_Status(void)
{
	// Read status
	unsigned char ch;
	int i;
	
	NF_nFCE_L();

	NF_CMD(0x70);
	for(i=0; i<10; i++);
	ch = NF_RDDATA();

	NF_nFCE_H();

	return ch;
}

int NF8_EraseBlock(unsigned int block)
{
	unsigned int blockPage=(block<<5);    


    NFConDone=0;
    rNFCONT|=(1<<9);
    rNFCONT|=(1<<10);
//    pISR_NFCON= (unsigned int)NFCon_Int;; //njs, need replace by ecos
    rSRCPND=BIT_NFCON;
    rINTMSK &=~(BIT_NFCON);

	NF_nFCE_L();
    
	NF_CMD(0x60);   // Erase one block 1st command, Block Addr:A9-A25
	// Address 3-cycle
	NF_ADDR(blockPage&0xff);	    // Page number=0
	NF_ADDR((blockPage>>8)&0xff);   
	NF_ADDR((blockPage>>16)&0xff);

  
	NF_CLEAR_RB();
	NF_CMD(0xd0);	// Erase one blcok 2nd command

//	NF_DETECT_RB();

    while(NFConDone==0);
	rNFCONT&=~(1<<9);
	rNFCONT&=~(1<<10); // Disable Illegal Access Interrupt
	if(rNFSTAT&0x20) return FAIL;
    
	NF_CMD(0x70);   // Read status command

      if (NF_RDDATA()&0x1) // Erase error
      {	
    	NF_nFCE_H();
		rGPGDAT|=(1<<1);
		nand_printf("[ERASE_ERROR:block#=%d]\n",block);
		NF8_MarkBadBlock(block);
		return FAIL;
       }
       else 
       {
    	NF_nFCE_H();
       return OK;
       }
}


int Adv_NF8_EraseBlock(unsigned int block)
{
	unsigned int blockPage=(block<<6);
    
//    NFConDone=0;
//    rNFCONT|=(1<<9);
//    rNFCONT|=(1<<10);
//    pISR_NFCON= (unsigned int)NFCon_Int;//njs, need replace by ecos
//    rSRCPND=BIT_NFCON;
//    rINTMSK&=~(BIT_NFCON);
	NF_nFCE_L();
    
	NF_CMD(0x60);   // Erase one block 1st command, Block Addr:A9-A25
	// Address 3-cycle
	NF_ADDR(blockPage&0xff);	    // Page number=0
	NF_ADDR((blockPage>>8)&0xff);   
	NF_ADDR((blockPage>>16)&0xff);


	NF_CLEAR_RB();
	NF_CMD(0xd0);	// Erase one blcok 2nd command
	NF_DETECT_RB();
//    while(NFConDone==0);
//	rNFCONT&=~(1<<9);
//	rNFCONT&=~(1<<10); // Disable Illegal Access Interrupt
//	if(rNFSTAT&0x20) return FAIL;

	NF_CMD(0x70);   // Read status command

      if (NF_RDDATA()&0x1) // Erase error
      {	
    	NF_nFCE_H();
		nand_printf("[ERASE_ERROR:block#=%d]\n",block);
//		NF8_MarkBadBlock(block);
		Adv_NF8_IsBadBlock(block);
		return FAIL;
      }
       else 
       {
    	NF_nFCE_H();
    	return OK;
      }
}


int NF8_IsBadBlock(unsigned int block)
{    
    unsigned int blockPage;
	unsigned char data;
    
    
    blockPage=(block<<5);	// For 2'nd cycle I/O[7:5] 
    
	NF_nFCE_L();
	NF_CLEAR_RB();

	NF_CMD(0x50);		 // Spare array read command
	NF_ADDR((512+5)&0xf);		 // Read the mark of bad block in spare array(M addr=5), A4-A7:Don't care
	NF_ADDR(blockPage&0xff);	 // The mark of bad block is in 0 page
	NF_ADDR((blockPage>>8)&0xff);	 // For block number A[24:17]
	NF_ADDR((blockPage>>16)&0xff);  // For block number A[25]
	 
	NF_DETECT_RB();	 // Wait tR(max 12us)

    data=NF_RDDATA();

	NF_nFCE_H();    

     if(data!=0xff)
     {
    	nand_printf("[block %d has been marked as a bad block(%x)]\n",block,data);
    	return FAIL;
     }
     else
     {
    	return OK;
     }
}

// Badblock return fail.else ok
int Adv_NF8_IsBadBlock(unsigned int block)
{
	unsigned int blockPage;
	unsigned char data;


	blockPage=(block<<6);	// For 2'nd cycle I/O[7:5] 

	NF_nFCE_L();
	NF_CLEAR_RB();
	
	NF_CMD(0x00);		 // read command
	NF_ADDR((2048+0)&0xff);			// 2060 = 0x080c
	NF_ADDR(((2048+0)>>8)&0xff);		// A[10:8]
	NF_ADDR((blockPage)&0xff);		// A[11;18]
	NF_ADDR((blockPage>>8)&0xff);	// A[26:19]
	NF_ADDR((blockPage>>16)&0xff);	// A27
	NF_CMD(0x30);	// 2'nd command

	NF_DETECT_RB();	 // Wait tR(max 12us)

	data=NF_RDDATA();

	NF_nFCE_H();    

	if(data!=0xff)
	{
		nand_printf("[block %d has been marked as a bad block(%x)]\n",block,data);
		return FAIL;
	}
	else
	{
		return OK;
	}
}


int NF8_MarkBadBlock(unsigned int block)
{
	int i;
	unsigned int blockPage=(block<<5);

	se8Buf[0]=0xff;
	se8Buf[1]=0xff;    
	se8Buf[2]=0xff;    
	se8Buf[5]=0x44;   // Bad blcok mark=44

	NF_nFCE_L(); 
	NF_CMD(0x50);   // pointing spare region (plane 50h)
	NF_CMD(0x80);   // Write 1st command

	NF_ADDR(0x0);		    // The mark of bad block is 
	NF_ADDR(blockPage&0xff);	    // marked 5th spare array 
	NF_ADDR((blockPage>>8)&0xff);   // in the 1st page.
	NF_ADDR((blockPage>>16)&0xff);  //

	for(i=0;i<16;i++)
	{
		NF_WRDATA(se8Buf[i]);	// Write spare array
	}

	NF_CLEAR_RB();
	NF_CMD(0x10);   // Write 2nd command
	NF_DETECT_RB();

	NF_CMD(0x70);

	for(i=0;i<3;i++);  //twhr=60ns////??????

	if (NF_RDDATA()&0x1) // Spare arrray write error
	{	
		NF_nFCE_H();
		nand_printf("[Program error is occurred but ignored]\n");
	}
	else 
	{
		NF_nFCE_H();
	}

	nand_printf("[block #%d is marked as a bad block]\n",block);
	return OK;
}

int Adv_NF8_MarkBadBlock(unsigned int block)
{
	int i;
	unsigned int blockPage=(block<<6);

	NF_nFCE_L(); 
	NF_CMD(0x80);   // Write 1st command

	NF_ADDR((2048+0)&0xff);			// 2060 = 0x080c
	NF_ADDR(((2048+0)>>8)&0xff);		// A[10:8]
	NF_ADDR((blockPage)&0xff);		// A[11;18]
	NF_ADDR((blockPage>>8)&0xff);	// A[26:19]
	NF_ADDR((blockPage>>16)&0xff);	// A27

	NF_WRDATA(0xaa);	// Write spare array
	NF_WRDATA(0xaa);
	
	NF_CLEAR_RB();
	NF_CMD(0x10);   // Write 2nd command
	NF_DETECT_RB();

	NF_CMD(0x70);

	for(i=0;i<3;i++);  //twhr=60ns////??????

	if (NF_RDDATA()&0x1) // Spare arrray write error
	{	
		NF_nFCE_H();
		nand_printf("[Program error is occurred but ignored]\n");
	}
	else 
	{
		NF_nFCE_H();
	}

	nand_printf("[block #%d is marked as a bad block]\n",block);
	return OK;
}
int NF8_ReadPage(unsigned int block,unsigned int page,unsigned char *buffer)
{
	unsigned int i, blockPage;
	unsigned int Mecc, Secc;
	unsigned char *bufPt=buffer;	

	blockPage=(block<<5)+page;
	NF_RSTECC();    // Initialize ECC
	NF_MECC_UnLock();

	NF_nFCE_L();    

	NF_CLEAR_RB();

	NF_CMD(0x00);	// Read command

	NF_ADDR(0); 	// Column = 0
	NF_ADDR(blockPage&0xff);		//
	NF_ADDR((blockPage>>8)&0xff);	// Block & Page num.
	NF_ADDR((blockPage>>16)&0xff);	//

	NF_DETECT_RB();


#if NAND_TRANS_MODE==NAND_CLANG
	for(i=0;i<512;i++) {
	*bufPt++=NF_RDDATA8();	// Read one page
	 }
#elif NAND_TRANS_MODE==NAND_DMA
	// Nand to memory dma setting
	rSRCPND=BIT_NAND_DMA;	// Init NAND_DMA src pending.
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rDISRC0=NFDATA; 	// Nand flash data register
	rDISRCC0=(0<<1) | (1<<0); //arc=AHB,src_addr=fix
	rDIDST0=(unsigned)bufPt;
	rDIDSTC0=(0<<1) | (0<<0); //dst=AHB,dst_addr=inc;
	rDCON0=(1<<31)|(1<<30)|(1<<29)|(1<<28)|(1<<27)|(0<<23)|(1<<22)|(2<<20)|(512/4/4);
	//Handshake,AHB,interrupt,(4-burst),whole,S/W,no_autoreload,word,count=128;

	// NAND_DMA on and start.
	rNAND_DMASKTRIG0=(1<<1)|(1<<0);

	while(!(rSUBSRCPND & BIT_SUB_NAND_DMA0));	// Wait until Dma transfer is done.

	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rSRCPND=BIT_NAND_DMA;
#endif

	NF_MECC_Lock();

	NF_SECC_UnLock();
	Mecc=NF_RDDATA();
	rNFMECCD0=((Mecc&0xff00)<<8)|(Mecc&0xff);
	rNFMECCD1=((Mecc&0xff000000)>>8)|((Mecc&0xff0000)>>16);

	NF_SECC_Lock();
	NF8_Spare_Data[0]=Mecc&0xff;
	NF8_Spare_Data[1]=(Mecc&0xff00)>>8;
	NF8_Spare_Data[2]=(Mecc&0xff0000)>>16;
	NF8_Spare_Data[3]=(Mecc&0xff000000)>>24;
	Mecc=NF_RDDATA();  // read 4~7
	NF8_Spare_Data[4]=Mecc&0xff;
	NF8_Spare_Data[5]=(Mecc&0xff00)>>8;
	NF8_Spare_Data[6]=(Mecc&0xff0000)>>16;
	NF8_Spare_Data[7]=(Mecc&0xff000000)>>24;

	Secc=NF_RDDATA();
	rNFSECCD=((Secc&0xff00)<<8)|(Secc&0xff);
	NF8_Spare_Data[8]=Secc&0xff;
	NF8_Spare_Data[9]=(Secc&0xff00)>>8;
	NF8_Spare_Data[10]=(Secc&0xff0000)>>16;
	NF8_Spare_Data[11]=(Secc&0xff000000)>>24;

	Secc=NF_RDDATA();
	NF8_Spare_Data[12]=Secc&0xff;
	NF8_Spare_Data[13]=(Secc&0xff00)>>8;
	NF8_Spare_Data[14]=(Secc&0xff0000)>>16;
	NF8_Spare_Data[15]=(Secc&0xff000000)>>24;
	NF_nFCE_H();    

	if ((rNFECCERR0&0xf) == 0x0){
	//       nand_printf("ECC OK!\n");
	return OK;
	}
	else {
	nand_printf("ECC FAIL!\n");
	nand_printf("NFECCERR0: 0x%x\n", rNFECCERR0);

	return FAIL;
	}
}

///////////////Advanced nand flash //////////////////////

int Adv_NF8_ReadPage(unsigned int block,unsigned int page,unsigned char *buffer)
{
	int i;
	unsigned int blockPage;
	unsigned int Mecc, Secc;
	unsigned char *bufPt=buffer;	   

	blockPage=(block<<6)+page;
	NF_RSTECC();    // Initialize ECC
	NF_MECC_UnLock();
 	  
	NF_nFCE_L();    

	NF_CLEAR_RB();

	NF_CMD(0x00);	// Read command
	NF_ADDR(0); 	// Column (A[7:0]) = 0
	NF_ADDR(0);		// A[11:8]
	NF_ADDR((blockPage)&0xff);	// A[19:12]
	NF_ADDR((blockPage>>8)&0xff);	// A[27:20]
	NF_ADDR((blockPage>>16)&0xff);	// A[27:20]

	NF_CMD(0x30);	// 2'nd command
	NF_DETECT_RB();

#if NAND_TRANS_MODE==NAND_CLANG
	for(i=0;i<2048;i++) {
		*bufPt++=NF_RDDATA8();	// Read one page
	}
#elif NAND_TRANS_MODE==NAND_DMA
	// Nand to memory dma setting
	rSRCPND=BIT_NAND_DMA;	// Init NAND_DMA src pending.
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rDISRC0=NFDATA; 	// Nand flash data register
	rDISRCC0=(0<<1) | (1<<0); //arc=AHB,src_addr=fix
	rDIDST0=(unsigned)bufPt;
	rDIDSTC0=(0<<1) | (0<<0); //dst=AHB,dst_addr=inc;
	rDCON0=(1<<31)|(1<<30)|(1<<29)|(1<<28)|(1<<27)|(0<<23)|(1<<22)|(2<<20)|(2048/4/4);
	//Handshake,AHB,interrupt,(4-burst),whole,S/W,no_autoreload,word,count=128;

	// NAND_DMA on and start.
	rNAND_DMASKTRIG0=(1<<1)|(1<<0);

	while(!(rSUBSRCPND & BIT_SUB_NAND_DMA0));	// Wait until Dma transfer is done.

	rSUBSRCPND|=BIT_SUB_NAND_DMA0;
	rSRCPND|=BIT_NAND_DMA;
#endif


	NF_MECC_Lock();

	NF_SECC_UnLock();
	Adv_NF8_Spare_Data[0]=NF_RDDATA8();
	Mecc=NF_RDDATA();
	rNFMECCD0=((Mecc&0xff00)<<8)|(Mecc&0xff);
	rNFMECCD1=((Mecc&0xff000000)>>8)|((Mecc&0xff0000)>>16);

	Adv_NF8_Spare_Data[1]=Mecc&0xff;
	Adv_NF8_Spare_Data[2]=(Mecc&0xff00)>>8;
	Adv_NF8_Spare_Data[3]=(Mecc&0xff0000)>>16;
	Adv_NF8_Spare_Data[4]=(Mecc&0xff000000)>>24;

	Adv_NF8_Spare_Data[5]=NF_RDDATA8();  // read 5
	Adv_NF8_Spare_Data[6]=NF_RDDATA8();  // read 6
	Adv_NF8_Spare_Data[7]=NF_RDDATA8();  // read 7

	NF_SECC_Lock();
	Secc=NF_RDDATA();
	rNFSECCD=((Secc&0xff00)<<8)|(Secc&0xff);
	Adv_NF8_Spare_Data[8]=Secc&0xff;
	Adv_NF8_Spare_Data[9]=(Secc&0xff00)>>8;
	Adv_NF8_Spare_Data[10]=(Secc&0xff0000)>>16;
	Adv_NF8_Spare_Data[11]=(Secc&0xff000000)>>24;

	for(i=12;i<64;i++) {
		Adv_NF8_Spare_Data[i]=NF_RDDATA8();	// Read spare array with 4byte width
	}

//	NF_CMD(0x70);   // Read status command

	NF_nFCE_H();    
	if ((rNFECCERR0&0xf) == 0x0){
//		nand_printf("ECC OK!\n");
//		MMU_InvalidateDCacheMVA((u32)(buffer));
//		MMU_CleanDCacheMVA((u32)(buffer));
		return OK;
	}
	else {
//		nand_printf("ECC FAIL!\n");
		return FAIL;
	}


}
		

int NF8_WritePage(unsigned int block,unsigned int page,unsigned char *buffer)
{
       int i;
	unsigned int blockPage, Mecc, Secc;
	unsigned char *bufPt=buffer;

	NFConDone=0;
    rNFCONT|=(1<<9);
    rNFCONT|=(1<<10);
//    pISR_NFCON= (unsigned int)NFCon_Int;//njs, need replace by ecos
    rSRCPND=BIT_NFCON;
    rINTMSK &=~(BIT_NFCON);
	  
	NF_RSTECC();    // Initialize ECC
   	NF_MECC_UnLock();
	blockPage=(block<<5)+page;

	NF_nFCE_L(); 
	
	NF_CMD(0x0);	// pointing main area plane 00h
	NF_CMD(0x80);   // Write 1st command

	NF_ADDR(0);			    // Column 0
	NF_ADDR(blockPage&0xff);	    //
	NF_ADDR((blockPage>>8)&0xff);   // Block & page num.
	NF_ADDR((blockPage>>16)&0xff);  //

	
#if NAND_TRANS_MODE==NAND_CLANG
	for(i=0;i<512;i++) {
	 	 {NF_WRDATA8((char)(*bufPt++));}	// Write one page to NFM from buffer
    }
#elif NAND_TRANS_MODE==NAND_DMA
	// Memory to Nand dma setting
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rSRCPND=BIT_NAND_DMA;	// Init NAND_DMA src pending.
	
	rDISRC0=(unsigned)bufPt; 	// Nand flash data register
	rDISRCC0=(0<<1) | (0<<0); //arc=AHB,src_addr=inc
	rDIDST0=NFDATA;
	rDIDSTC0=(0<<1) | (1<<0); //dst=AHB,dst_addr=fix;
	rDCON0=(1<<31)|(1<<30)|(1<<29)|(0<<28)|(1<<27)|(0<<23)|(1<<22)|(2<<20)|(512/4);
	//  only unit transfer in writing!!!!
	//Handshake,AHB,interrupt,(unit),whole,S/W,no_autoreload,word,count=128;
	
	// NAND_DMA on and start.
	rNAND_DMASKTRIG0=(1<<1)|(1<<0);
	
	while(!(rSUBSRCPND & BIT_SUB_NAND_DMA0));	// Wait until Dma transfer is done.
	
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rSRCPND=BIT_NAND_DMA;	
#endif


    NF_MECC_Lock();
	// Get ECC data.
	// Spare data for 8bit
	// byte  0     1    2     3     4          5               6      7            8         9
	// ecc  [0]  [1]  [2]  [3]    x   [Bad marking]                    SECC0  SECC1
	Mecc = rNFMECC0;
	
	se8Buf[0]=(unsigned char)(Mecc&0xff);
	se8Buf[1]=(unsigned char)((Mecc>>8) & 0xff);
	se8Buf[2]=(unsigned char)((Mecc>>16) & 0xff);
	se8Buf[3]=(unsigned char)((Mecc>>24) & 0xff);
	se8Buf[5]=0xff;		// Marking good block

	NF_SECC_UnLock();

	//Write extra data(ECC, bad marking)
	for(i=0;i<4;i++) {
		NF_WRDATA8(se8Buf[i]);	// Write spare array(Main ECC)
		NF8_Spare_Data[i]=se8Buf[i];
    	}  
    NF_SECC_Lock(); 
	Secc=rNFSECC; 
	se8Buf[8]=(unsigned char)(Secc&0xff);
	se8Buf[9]=(unsigned char)((Secc>>8) & 0xff);
	for(i=4;i<16;i++) {
		NF_WRDATA8(se8Buf[i]);  // Write spare array(Spare ECC and Mark)
		NF8_Spare_Data[i]=se8Buf[i];
	}  
 	NF_CLEAR_RB();
	NF_CMD(0x10);	 // Write 2nd command

	NF_DETECT_RB();
//	while(NFConDone==0);
	 rNFCONT&=~(1<<9);
	 rNFCONT&=~(1<<10); // Disable Illegal Access Interrupt
	 if(rNFSTAT&0x20) return FAIL;


	NF_CMD(0x70);   // Read status command   
    
	for(i=0;i<3;i++);  //twhr=60ns
    
    if (NF_RDDATA()&0x1) {// Page write error
        NF_nFCE_H();
	 	nand_printf("[PROGRAM_ERROR:block#=%d]\n",block);
		NF8_MarkBadBlock(block);
		return FAIL;
       }
     else {
        NF_nFCE_H();
	      return OK;
	}

}

//////////////// Advanced nand flash ////////////////////////////////

int Adv_NF8_WritePage(unsigned int block,unsigned int page,const unsigned char *buffer)
{
    int i;
	unsigned int blockPage, Mecc, Secc;
	const unsigned char *bufPt=buffer;
//	NFConDone=0;
//    rNFCONT|=(3<<9);
//    pISR_NFCON= (unsigned)NFCon_Int;
//    rSRCPND=BIT_NFCON;
//    rINTMSK &=~(BIT_NFCON);
		
	NF_RSTECC();    // Initialize ECC
    NF_MECC_UnLock();
	blockPage=(block<<6)+page;

	NF_nFCE_L(); 
	NF_CLEAR_RB();
	NF_CMD(0x80);   // Write 1st command
	NF_ADDR(0); 	// Column (A[7:0]) = 0
	NF_ADDR(0); 	// A[11:8]
	NF_ADDR((blockPage)&0xff);	// A[19:12]
	NF_ADDR((blockPage>>8)&0xff);	// A[27:20]
	NF_ADDR((blockPage>>16)&0xff);	// A[27:20]
	
#if NAND_TRANS_MODE==NAND_CLANG
     
	for(i=0;i<2048;i++) {
		NF_WRDATA8(*bufPt++);	// Write one page to NFM from buffer
    }
#elif NAND_TRANS_MODE==NAND_DMA
	// Memory to Nand dma setting
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rSRCPND=BIT_NAND_DMA;	// Init NAND_DMA src pending.
	rDISRC0=(unsigned)bufPt; 	// Nand flash data register
	rDISRCC0=(0<<1) | (0<<0); //arc=AHB,src_addr=inc
	rDIDST0=NFDATA;
	rDIDSTC0=(0<<1) | (1<<0); //dst=AHB,dst_addr=fix;
	rDCON0=(1<<31)|(1<<30)|(1<<29)|(0<<28)|(1<<27)|(0<<23)|(1<<22)|(2<<20)|(2048/4);
	//  only unit transfer in writing!!!!
	//Handshake,AHB,interrupt,(unit),whole,S/W,no_autoreload,word,count=128;
	
	// NAND_DMA on and start.
	rNAND_DMASKTRIG0=(1<<1)|1;	//channel on
//	rNAND_DMASKTRIG0=(1<<0);	// trigger
	while(!(rSUBSRCPND & BIT_SUB_NAND_DMA0));	// Wait until Dma transfer is done.
	
	rSUBSRCPND=BIT_SUB_NAND_DMA0;
	rSRCPND=BIT_NAND_DMA;	
#endif

    NF_MECC_Lock();
	// Get ECC data.
	// Spare data for 8bit
	// byte  0                  1    2     3     4          5               6      7            8         9
	// ecc  [Bad marking] [0]  [1]  [2]  [3]    x                       SECC0  SECC1
	Mecc = rNFMECC0;

	Adv_se8Buf[0]=0xff;
	Adv_se8Buf[1]=(unsigned char)(Mecc&0xff);
	Adv_se8Buf[2]=(unsigned char)((Mecc>>8) & 0xff);
	Adv_se8Buf[3]=(unsigned char)((Mecc>>16) & 0xff);
	Adv_se8Buf[4]=(unsigned char)((Mecc>>24) & 0xff);
			// Marking good block

	NF_SECC_UnLock();
	//Write extra data(ECC, bad marking)
	for(i=0;i<5;i++) {
		NF_WRDATA8(Adv_se8Buf[i]);	// Write spare array(Main ECC)
		Adv_NF8_Spare_Data[i]=Adv_se8Buf[i];
    	}  
    NF_SECC_Lock(); 
	Secc=rNFSECC; 
	Adv_se8Buf[8]=(unsigned char)(Secc&0xff);
	Adv_se8Buf[9]=(unsigned char)((Secc>>8) & 0xff);
	
	for(i=5;i<64;i++) {
		NF_WRDATA8(Adv_se8Buf[i]);  // Write spare array(Spare ECC and Mark)
		Adv_NF8_Spare_Data[i]=Adv_se8Buf[i];
	}  
	NF_CMD(0x10);	 // Write 2nd command
	for(i=0;i<10;i++);  //twhr=60ns	
	NF_DETECT_RB();
//	while(NFConDone==0);
//	 rNFCONT&=~(1<<9);
//	 rNFCONT&=~(1<<10); // Disable Illegal Access Interrupt
//	 if(rNFSTAT&0x20) return FAIL;

	NF_CMD(0x70);   // Read status command   
    
	for(i=0;i<10;i++);  //twhr=60ns
    if (NF_RDDATA()&0x1) {// Page write error
	    NF_nFCE_H();    
		nand_printf("[PROGRAM_ERROR:block#=%d]\n",block);
		Adv_NF8_IsBadBlock(block);
		return FAIL;
    } else {
	    NF_nFCE_H();    
	    return OK;
	}
	
}



unsigned short NF8_CheckId(void)
{
    int i;
    unsigned short id;
    unsigned char id0, id1, id2, id3;
//    rEBICON|=(1<<8);
    
    NF_nFCE_L();
 //   NF_nCS1_L();
	
    NF_CMD(0x90);
    NF_ADDR(0x0);

    for (i=0; i<10; i++);
//    nand_printf("NFSTAT: 0x%x\n", rNFSTAT);

    id0=NF_RDDATA8();	// Maker code 0xec
    id1=NF_RDDATA8();	// Devide code(K9S1208V:0x76), (K9K2G16U0M:0xca)
    id2=NF_RDDATA8();
    id3=NF_RDDATA8();
    
    id=(id0<<8)|(id1);
    NF_nFCE_H();
 //   NF_nCS1_H();
    nand_printf("id0:0x%02x, id1:0x%02x,id2:0x%02x,id3:0x%02x \n", id0, id1, id2, id3);
    return id;
}
				  

void Nand_Reset(void)
{
    	int i;
   
	NF_nFCE_L();

	NF_CLEAR_RB();
	NF_CMD(0xFF);	//reset command
	
	for(i=0;i<10;i++);  //tWB = 100ns. //??????
	NF_DETECT_RB();
	
	NF_nFCE_H();

}


void NF8_Init(void)
{
	// for S3C2413

	rNFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4)|(1<<3)|(1<<2)|(1<<1)|(0<<0);	
	// TACLS		[14:12]	CLE&ALE duration = HCLK*TACLS.
	// TWRPH0		[10:8]	TWRPH0 duration = HCLK*(TWRPH0+1)
	// TWRPH1		[6:4]	TWRPH1 duration = HCLK*(TWRPH1+1)
	// AdvFlash(R)	[3]		Advanced NAND, 0:256/512, 1:1024/2048
	// PageSize(R)	[2]		NAND memory page size
	//						when [3]==0, 0:256, 1:512 bytes/page.
	//						when [3]==1, 0:1024, 1:2048 bytes/page.
	// AddrCycle(R)	[1]		NAND flash addr size
	//						when [3]==0, 0:3-addr, 1:4-addr.
	//						when [3]==1, 0:4-addr, 1:5-addr.
	// BusWidth(R/W) [0]	NAND bus width. 0:8-bit, 1:16-bit.
	
	//rNFCONT = (0<<17)|(0<<16)|(0<<10)|(0<<9)|(0<<8)|(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<1)|(1<<0);
	rNFCONT = (0<<17)|(0<<16)|(0<<10)|(0<<9)|(0<<8)|(1<<7)|(1<<6)|(1<<5)|(1<<4)|(0x3<<1)|(1<<0);
	// Lock-tight	[17]	0:Disable lock, 1:Enable lock.
	// Soft Lock	[16]	0:Disable lock, 1:Enable lock.
	// EnablillegalAcINT[10]	Illegal access interupt control. 0:Disable, 1:Enable
	// EnbRnBINT	[9]		RnB interrupt. 0:Disable, 1:Enable
	// RnB_TrandMode[8]		RnB transition detection config. 0:Low to High, 1:High to Low
	// SpareECCLock	[7]		0:Unlock, 1:Lock
	// MainECCLock	[6]		0:Unlock, 1:Lock
	// InitMECC(W)	[5]		1:Init main area ECC decoder/encoder.
	// InitSECC(W)	[4]		1:Init spare area ECC decoder/encoder.
	// Reg_nCE1		[2]		0:nFCE=0, 1:nFCE=1.
	// Reg_nCE0		[1]		0:nFCE=0, 1:nFCE=1.
	// NANDC Enable	[0]		operating mode. 0:Disable, 1:Enable.
//	rNFSTAT = 0;
    Nand_Reset();
#if NAND_TRANS_MODE==NAND_DMA	
	rDMAREQSEL0=0;	////S/W request mode
    rINTMSK |=BIT_DMA;	//½ûÖ¹ËùÓÐdmaÖÐ¶Ï
    rINTSUBMSK |=BIT_SUB_DMA0;
	rDMASKTRIG0 |= (0x1<<2);	//stop dma
#endif
	
}
  
