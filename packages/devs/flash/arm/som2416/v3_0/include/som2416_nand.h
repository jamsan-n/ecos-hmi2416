#ifndef SOM2416_NAND_H
#define SOM2416_NAND_H

#ifdef __cplusplus
extern "C" {
#endif


#define FAIL 0
#define OK   1

#define NAND_ASM		1
#define NAND_CLANG	2
#define NAND_DMA		3
#define NAND_TRANS_MODE 2


#define NF_MECC_UnLock()         {rNFCONT&=~(1<<7);}
#define NF_MECC_Lock()         {rNFCONT|=(1<<7);}
#define NF_SECC_UnLock()         {rNFCONT&=~(1<<6);}
#define NF_SECC_Lock()         {rNFCONT|=(1<<6);}
#define NF_CMD(cmd)			{rNFCMD=cmd;}
#define NF_ADDR(addr)		{rNFADDR=addr;}	
#define NF_nCS1_L()			{rNFCONT&=~(1<<2);}
#define NF_nCS1_H()			{rNFCONT|=(1<<2);}
#define NF_nFCE_L()			{rNFCONT&=~(1<<1);}
#define NF_nFCE_H()			{rNFCONT|=(1<<1);}
#define NF_RSTECC()			{rNFCONT|=(1<<5)|(1<<4);}
#define NF_RDDATA() 			(rNFDATA)
#define NF_RDDATA8() 		((*(volatile unsigned char*)0x4E000010) )
#define NF_RDDATA16() 		((*(volatile unsigned short*)0x4E000010) )
#define NF_WRDATA(data) 	{rNFDATA=data;}
#define NF_WRDATA8(data) 	{rNFDATA8=data;}

// RnB Signal
#define NF_CLEAR_RB()    		{rNFSTAT |= (1<<4);}	// Have write '1' to clear this bit.
#define NF_DETECT_RB()    		{while(!(rNFSTAT&(1<<4)));}


#define ID_K9S1208V0M	0xec76
#define ID_KMXD64P3 	0x9876
#define ID_K9K2G08U0M	0xecda
#define ID_K9K2G16U0M	0xecca

#define NAND_ID ID_K9K2G08U0M

#if NAND_ID==ID_K9K2G08U0M
#define BLOCKS_INNAND	2048
#define PAGES_PERBLOCK	64
#define BYTES_PERPAGE	2048
#define BYTES_PERBLOCK	(BYTES_PERPAGE*PAGES_PERBLOCK)
#endif
// HCLK=100Mhz
/*
#define TACLS		1	// 1-clk(0ns) 
#define TWRPH0		3	// 3-clk(25ns)
#define TWRPH1		1	// 1-clk(10ns)  //TACLS+TWRPH0+TWRPH1>=50ns
  */
  
// HCLK=133Mhz  (MLC, K9HBG08U)
/*
#define TACLS		1	// 1-clk(7.5ns) 
#define TWRPH0		3	// 3-clk(22.5ns)
#define TWRPH1		1	// 2-clk(15ns)  //TACLS+TWRPH0+TWRPH1>=30ns
  */

// HCLK=133Mhz  (MLC, K9K2G08)
/*
#define TACLS		1	// 1-clk(7.5ns) 
#define TWRPH0		4	// 5-clk(38.5ns)
#define TWRPH1		1	// 2-clk(15ns)  //TACLS+TWRPH0+TWRPH1>=30ns
  */

// HCLK=133Mhz (SLC, K9F2G08)
#define TACLS		1	// 1-clk(7.5ns) , min 12ns
#define TWRPH0		2	// 3-clk(22.5ns), twp=12ns
#define TWRPH1		1	// 2-clk(15ns)  //TACLS+TWRPH0+TWRPH1>=30ns, tdh=5ns
/*
#define TACLS		7	// 1-clk(7.5ns) 
#define TWRPH0		7	// 3-clk(22.5ns)
#define TWRPH1		7	// 2-clk(15ns)  //TACLS+TWRPH0+TWRPH1>=30ns
*/

#define BAD_MARK	(0x44444444)


//*************** H/W dependent functions ***************
// Assembler code for speed

void Nand_Reset(void);
void InputTargetBlock(void);
void NF8_Print_Id(void);
 unsigned short NF8_CheckId(void);
 int NF8_EraseBlock(unsigned int blockNum);
 int NF8_ReadPage(unsigned int block,unsigned int page,unsigned char *buffer);
 int NF8_WritePage(unsigned int block,unsigned int page,unsigned char *buffer);
 int NF8_IsBadBlock(unsigned int block);
 int NF8_MarkBadBlock(unsigned int block);


int Adv_NF8_EraseBlock(unsigned int block);
int Adv_NF8_ReadPage(unsigned int block,unsigned int page,unsigned char *buffer);
int Adv_NF8_WritePage(unsigned int block,unsigned int page,const unsigned char *buffer);
int Adv_NF8_IsBadBlock(unsigned int block);
int Adv_NF8_MarkBadBlock(unsigned int block);

 void NF8_Init(void);


//*******************************************************

#ifdef __cplusplus
}
#endif

#endif /*__NAND_H*/

