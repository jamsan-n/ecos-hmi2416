//=============================================================================
// File Name : 2450addr.h
// Function  : S3C2450 Define Address Register
// History
//   0.0 : Programming start (February 22,2008)
//=============================================================================

#ifndef __2450ADDR_H__
#define __2450ADDR_H__

#ifdef __cplusplus
extern "C" {
#endif

#define SOM2416_SDRAM_PHYS_BASE         0x30000000
#define SOM2416_SDRAM_VIRT_BASE         0x00000000

#define SOM2416_FLASH_PHYS_BASE         0x00000000
#define SOM2416_FLASH_VIRT_BASE         0x80000000


// Internal clocks
#define FCLK CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK
#define HCLK CYGNUM_HAL_ARM_SOM2416_BUS_CLOCK
#define PCLK CYGNUM_HAL_ARM_SOM2416_PERIPHERAL_CLOCK
#define UCLK 48000000

//==============================================================================================================
//	Fin = 12MHz,
//
//	MPLLout = (m x Fin)/(p x 2^s), m=MDIV, p=PDIV, s=SDIV, Fin=10~30MHz
//	(350,3,2)=350Mhz, (400,3,2)=400Mhz, (225,3,1)=450Mhz, (250,3,1)=498Mhz, (267,3,1)=534Mhz, (400,3,1)=800Mhz
//
//	EPLLout = ((m + K/2^16)xFin)/(p x 2^s), m=MDIV, p=PDIV, s=SDIV, K=KDIV, Fin=10~40MHz
//	(48,1,4)=36Mhz, (32,1,3)=48Mhz, (40,1,3)=60Mhz, (48,1,3)=72Mhz, (28,1,2)=84Mhz, (32,1,2)=96Mhz
//===============================================================================================================

#define		FIN					12000000
//the follow 3 lines was replace by M_MDIV,M_PDIV,M_SDIV in plat_form_setup.h
//#define		Startup_MDIV		81	//ori 400/njs
//#define		Startup_PDIV		2	//ori 3
//#define		Startup_SDIV		1
#define		Startup_ARMCLKdiv	0		//	ori 1	 :	ARMCLK	= MPLL/1
																//	1	 :	ARMCLK	= MPLL/2
																//	2	 :	ARMCLK	= MPLL/3
																//	3	 :	ARMCLK	= MPLL/4
																//	5	 :	ARMCLK	= MPLL/6
																//	7	 :	ARMCLK	= MPLL/8
																//	13	 :	ARMCLK	= MPLL/12
																//	15	 :	ARMCLK	= MPLL/16

#define		Startup_PREdiv		1		//ori 2//	0x0  :	PREDIV_CLK	= MPLL
										//	0x1 :	PREDIV_CLK	= MPLL/2
										//	0x2 :	PREDIV_CLK	= MPLL/3
										//	0x3 :	PREDIV_CLK	= MPLL/4
																		
#define		Startup_HCLKdiv		1		//	0x0  :	HCLK	= PREDIV_CLK
										//	0x1 :	HCLK	= PREDIV_CLK/2
									    //	0x3 :	HCLK	= PREDIV_CLK/4

#define		Startup_PCLKdiv		1		//	0	 :	PCLK	= HCLK
										//	1	 :	PCLK	= HCLK/2

#define		tREFRESH		1037		//	'us' * 100

#define		tRAS			50		//	'ns'
#define		tARFC			80		//	'ns'
#define		tRCD			23		//	'ns'
#define		tRP				23		//	'ns'

#define		CL				3

// CLOCK & POWER MANAGEMENT
//#define LOCKTIME   0x4c000000  //PLL lock time counter
//#define MPLLCON    0x4c000004  //MPLL Control
//#define UPLLCON    0x4c000008  //UPLL Control
//#define CLKCON     0x4c00000c  //Clock generator control
//#define CLKSLOW    0x4c000010  //Slow clock control
//#define CLKDIVN    0x4c000014  //Clock divider control
//above was for test only, ------need to remove!!!!!!!!

// chapter2 SYSEM CONTROLLER - jcs
#define LOCKCON0    (0x4C000000)  		//MPLL lock time conut
#define LOCKCON1    (0x4C000004)  		//EPLL lock time count
#define OSCSET      (0x4C000008)  		//OSC stabilization control
#define MPLLCON     (0x4C000010)  		//MPLL configuration
#define EPLLCON     (0x4C000018)  		//EPLL configuration
#define EPLLCON_K   (0x4C00001C)  		//EPLL configuration
#define CLKSRC      (0x4C000020)  		//Clock source control
#define CLKDIV0     (0x4C000024)  		//Clock divider ratio control
#define CLKDIV1     (0x4C000028)  		//Clock divider ratio control
#define CLKDIV2     (0x4C00002C)  		//Clock divider ratio control
#define HCLKCON     (0x4C000030)  		//HCLK enable
#define PCLKCON     (0x4C000034)  		//PCLK enable
#define SCLKCON     (0x4C000038)  		//Special clock enable
#define PWRMODE     (0x4C000040)  		//Power mode control
#define SWRST       (0x4C000044)  		//Software reset control
#define BUSPRI0     (0x4C000050)  		//Bus priority control
#define PWRCFG      (0x4C000060)  		//Power management configuration control
#define RSTCON      (0x4C000064)  		//Reset control 
#define RSTSTAT     (0x4C000068)  		//Reset status
#define WKUPSTAT    (0x4C00006c)  		//Wakeup status
#define INFORM0     (0x4C000070)  		//Sleep mode information 0
#define INFORM1     (0x4C000074)  		//Sleep mode information 1
#define INFORM2     (0x4C000078)  		//Sleep mode information 2
#define INFORM3     (0x4C00007C)  		//Sleep mode information 3
#define USB_PHYCTRL (0x4C000080)  		//USB phy control
#define USB_PHYPWR  (0x4C000084)  		//USB phy power control
#define USB_RSTCON  (0x4C000088)  		//USB phy reset control
#define USB_CLKCON  (0x4C00008C)  		//USB phy clock control

// chapter2 SYSEM CONTROLLER - jcs
#define rLOCKCON0    (*(volatile unsigned *)0x4C000000)  		//MPLL lock time conut
#define rLOCKCON1    (*(volatile unsigned *)0x4C000004)  		//EPLL lock time count
#define rOSCSET      (*(volatile unsigned *)0x4C000008)  		//OSC stabilization control
#define rMPLLCON     (*(volatile unsigned *)0x4C000010)  		//MPLL configuration
#define rEPLLCON     (*(volatile unsigned *)0x4C000018)  		//EPLL configuration
#define rEPLLCON_K     (*(volatile unsigned *)0x4C00001C)  		//EPLL configuration
#define rCLKSRC      (*(volatile unsigned *)0x4C000020)  		//Clock source control
#define rCLKDIV0     (*(volatile unsigned *)0x4C000024)  		//Clock divider ratio control
#define rCLKDIV1     (*(volatile unsigned *)0x4C000028)  		//Clock divider ratio control
#define rCLKDIV2     (*(volatile unsigned *)0x4C00002C)  		//Clock divider ratio control
#define rHCLKCON     (*(volatile unsigned *)0x4C000030)  		//HCLK enable
#define rPCLKCON     (*(volatile unsigned *)0x4C000034)  		//PCLK enable
#define rSCLKCON     (*(volatile unsigned *)0x4C000038)  		//Special clock enable
#define rPWRMODE     (*(volatile unsigned *)0x4C000040)  		//Power mode control
#define rSWRST      (*(volatile unsigned *)0x4C000044)  		//Software reset control
#define rBUSPRI0     (*(volatile unsigned *)0x4C000050)  		//Bus priority control
#define rPWRCFG      (*(volatile unsigned *)0x4C000060)  		//Power management configuration control
#define rRSTCON      (*(volatile unsigned *)0x4C000064)  		//Reset control 
#define rRSTSTAT     (*(volatile unsigned *)0x4C000068)  		//Reset status
#define rWKUPSTAT    (*(volatile unsigned *)0x4C00006c)  		//Wakeup status
#define rINFORM0     (*(volatile unsigned *)0x4C000070)  		//Sleep mode information 0
#define rINFORM1     (*(volatile unsigned *)0x4C000074)  		//Sleep mode information 1
#define rINFORM2     (*(volatile unsigned *)0x4C000078)  		//Sleep mode information 2
#define rINFORM3     (*(volatile unsigned *)0x4C00007C)  		//Sleep mode information 3
#define rUSB_PHYCTRL (*(volatile unsigned *)0x4C000080)  		//USB phy control
#define rUSB_PHYPWR  (*(volatile unsigned *)0x4C000084)  		//USB phy power control
#define rUSB_RSTCON  (*(volatile unsigned *)0x4C000088)  		//USB phy reset control
#define rUSB_CLKCON  (*(volatile unsigned *)0x4C00008C)  		//USB phy clock control

// chapter3 EBI - oh
#define BPRIORITY0	 (0x4E800000)	//Matrix core 0 priority decision - edited by junon
#define BPRIORITY1	 (0x4E800004)	//Matrix core 1 priority decision - added by junon
#define EBICON   	 (0x4E800008)	//Bank Configuration - edited by junon


// chapter5 SSMC - junon
#define SMBIDCYR0   (0x4F000000)	//Bank0 idle cycle control 
#define SMBIDCYR1   (0x4F000020)	//Bank1 idle cycle control 
#define SMBIDCYR2   (0x4F000040)	//Bank2 idle cycle control 
#define SMBIDCYR3   (0x4F000060)	//Bank3 idle cycle control 
#define SMBIDCYR4   (0x4F000080)	//Bank0 idle cycle control 
#define SMBIDCYR5   (0x4F0000A0)	//Bank5 idle cycle control 
#define SMBWSTRDR0  (0x4F000004)	//Bank0 read wait state control 
#define SMBWSTRDR1  (0x4F000024)	//Bank1 read wait state control
#define SMBWSTRDR2  (0x4F000044)	//Bank2 read wait state control
#define SMBWSTRDR3  (0x4F000064)	//Bank3 read wait state control 
#define SMBWSTRDR4  (0x4F000084)	//Bank4 read wait state control 
#define SMBWSTRDR5  (0x4F0000A4)	//Bank5 read wait state control 
#define SMBWSTWRR0  (0x4F000008)	//Bank0 write wait state control 
#define SMBWSTWRR1  (0x4F000028)	//Bank1 write wait state control 
#define SMBWSTWRR2  (0x4F000048)	//Bank2 write wait state control 
#define SMBWSTWRR3  (0x4F000068)	//Bank3 write wait state control 
#define SMBWSTWRR4  (0x4F000088)	//Bank4 write wait state control 
#define SMBWSTWRR5  (0x4F0000A8)	//Bank5 write wait state control 
#define SMBWSTOENR0 (0x4F00000C)	//Bank0 output enable assertion delay control 
#define SMBWSTOENR1 (0x4F00002C)	//Bank1 output enable assertion delay control 
#define SMBWSTOENR2 (0x4F00004C)	//Bank2 output enable assertion delay control
#define SMBWSTOENR3 (0x4F00006C)	//Bank3 output enable assertion delay control 
#define SMBWSTOENR4 (0x4F00008C)	//Bank4 output enable assertion delay control
#define SMBWSTOENR5 (0x4F0000AC)	//Bank5 output enable assertion delay control 
#define SMBWSTWENR0 (0x4F000010)	//Bank0 write enable assertion delay control 
#define SMBWSTWENR1 (0x4F000030)	//Bank1 write enable assertion delay control 
#define SMBWSTWENR2 (0x4F000050)	//Bank2 write enable assertion delay control 
#define SMBWSTWENR3 (0x4F000070)	//Bank3 write enable assertion delay control 
#define SMBWSTWENR4 (0x4F000090)	//Bank4 write enable assertion delay control 
#define SMBWSTWENR5 (0x4F0000B0)	//Bank5 write enable assertion delay control 
#define SMBCR0      (0x4F000014)	//Bank0 control 
#define SMBCR1      (0x4F000034)	//Bank1 control 
#define SMBCR2      (0x4F000054)	//Bank2 control 
#define SMBCR3      (0x4F000074)	//Bank3 control 
#define SMBCR4      (0x4F000094)	//Bank4 control 
#define SMBCR5      (0x4F0000B4)	//Bank5 control 
#define SMBSR0      (0x4F000018)	//Bank0 status 
#define SMBSR1      (0x4F000038)	//Bank1 status 
#define SMBSR2      (0x4F000058)	//Bank2 status 
#define SMBSR3      (0x4F000078)	//Bank3 status 
#define SMBSR4      (0x4F000098)	//Bank4 status 
#define SMBSR5      (0x4F0000B8)	//Bank5 status 
#define SMBWSTBRDR0 (0x4F00001C)	//Bank0 burst read wait delay control 
#define SMBWSTBRDR1 (0x4F00003C)	//Bank1 burst read wait delay control 
#define SMBWSTBRDR2 (0x4F00005C)	//Bank2 burst read wait delay control 
#define SMBWSTBRDR3 (0x4F00007C)	//Bank3 burst read wait delay control 
#define SMBWSTBRDR4 (0x4F00009C)	//Bank4 burst read wait delay control 
#define SMBWSTBRDR5 (0x4F0000BC)	//Bank5 burst read wait delay control 
#define SMBONETYPER (0x4F000100)	//OneNAND type selection - added by junon
#define SMCSR		 (0x4F000200)	//SROMC status - edited by junon
#define SMCCR       (0x4F000204)	//SROMC control - edited by junon

#define SMC_REG_BASE 	0x4F000000	// added by junon
#define SMC_REG_OFFSET 	0x20

// chapter6 MOBILE DRAM CONTROLLER - oh
#define BANKCFG    (0x48000000)	//Mobile DRAM configuration
#define BANKCON1   (0x48000004)	//Mobile DRAM control 
#define BANKCON2   (0x48000008)	//Mobile DRAM timing control 
#define BANKCON3   (0x4800000C)	//Mobile DRAM (E)MRS 
#define REFRESH    (0x48000010)	//Mobile DRAM refresh control
#define TIMEOUT    (0x48000014)	//Write Buffer Time out control 


// chapter7 Nand Flash - jcs
// chapter7 Nand Flash - grmoon
// chapter7 Nand Flash - grmoon
#define NFCONF			(0x4E000000)		 
#define NFCONT			(0x4E000004)     
#define NFCMD			(0x4E000008)     
#define NFADDR			(0x4E00000C)     
#define NFDATA				(0x4E000010)     
#define NFDATA8			(0x4E000010)     
#define NFMECCD0			(0x4E000014)     
#define NFMECCD1			(0x4E000018)     
#define NFSECCD			(0x4E00001C)     
#define NFSBLK				(0x4E000020)	  	
#define NFEBLK				(0x4E000024)		 
#define NFSTAT				(0x4E000028) 	   
#define NFECCERR0		(0x4E00002C)     
#define NFECCERR1		(0x4E000030)     
#define NFMECC0			(0x4E000034)     
#define NFMECC1			(0x4E000038)     
#define NFSECC			(0x4E00003C)	   
#define NFMLCBITPT		(0x4E000040)  		
#define NF8ECCERR0	  	(0x4E000044)  		
#define NF8ECCERR1  		(0x4E000048)
#define NF8ECCERR2    		(0x4E00004C)
#define NFM8ECC0			(0x4E000050)
#define NFM8ECC1			(0x4E000054)
#define NFM8ECC2			(0x4E000058)
#define NFM8ECC3			(0x4E00005C)
#define NFMLC8BITPT0		(0x4E000060)
#define NFMLC8BITPT1		(0x4E000064)

#define rNFCONF			(*(volatile unsigned *)0x4E000000)		 
#define rNFCONT			(*(volatile unsigned *)0x4E000004)     
#define rNFCMD			(*(volatile unsigned *)0x4E000008)     
#define rNFADDR			(*(volatile unsigned *)0x4E00000C)     
#define rNFDATA				(*(volatile unsigned *)0x4E000010)     
#define rNFDATA8			(*(volatile unsigned char*)0x4E000010)     
#define rNFMECCD0			(*(volatile unsigned *)0x4E000014)     
#define rNFMECCD1			(*(volatile unsigned *)0x4E000018)     
#define rNFSECCD			(*(volatile unsigned *)0x4E00001C)     
#define rNFSBLK				(*(volatile unsigned *)0x4E000020)	  	
#define rNFEBLK				(*(volatile unsigned *)0x4E000024)		 
#define rNFSTAT				(*(volatile unsigned *)0x4E000028) 	   
#define rNFECCERR0		(*(volatile unsigned *)0x4E00002C)     
#define rNFECCERR1		(*(volatile unsigned *)0x4E000030)     
#define rNFMECC0			(*(volatile unsigned *)0x4E000034)     
#define rNFMECC1			(*(volatile unsigned *)0x4E000038)     
#define rNFSECC			(*(volatile unsigned *)0x4E00003C)	   
#define rNFMLCBITPT		(*(volatile unsigned *)0x4E000040)  		
#define rNF8ECCERR0	  	(*(volatile unsigned *)0x4E000044)  		
#define rNF8ECCERR1  		(*(volatile unsigned *)0x4E000048)
#define rNF8ECCERR2    		(*(volatile unsigned *)0x4E00004C)
#define rNFM8ECC0			(*(volatile unsigned *)0x4E000050)
#define rNFM8ECC1			(*(volatile unsigned *)0x4E000054)
#define rNFM8ECC2			(*(volatile unsigned *)0x4E000058)
#define rNFM8ECC3			(*(volatile unsigned *)0x4E00005C)
#define rNFMLC8BITPT0		(*(volatile unsigned *)0x4E000060)
#define rNFMLC8BITPT1		(*(volatile unsigned *)0x4E000064)

//chapter8 CF Interface 
#define MUX_REG             (0x4B801800) //Top level control & configuration register
#define PCCARD_CFG          (0x4B801820) //PC card configuration & status register
#define PCCARD_INT          (0x4B801824) //PC card interrupt mask & source regiseter
#define PCCARD_ATTR         (0x4B801828) //PC card attribute memory area operation timing config regiseter
#define PCCARD_IO           (0x4B80182C) //PC card I/O area operation timing config regiseter
#define PCCARD_COMM         (0x4B801830) //PC card common memory area operation timing config regiseter
#define ATA_CON             (0x4B801900) //ATA_CONTROL register
#define ATA_STAT            (0x4B801904) //ATA_STATUS register
#define ATA_CMD             (0x4B801908) //ATA transfer command
#define ATA_SWRST           (0x4B80190C) //Software reset for the ATAPI host
#define ATA_IRQ             (0x4B801910) //ATA_IRQ register
#define ATA_IRQ_MASK        (0x4B801914) //ATA_IRQ Mask register
#define ATA_CFG             (0x4B801918) //ATA_CFG register
#define ATA_PIO_TIME        (0x4B80192C) //ATA_PIO_TIME register
#define ATA_UDMA_TIME       (0x4B801930) //ATA_UDMA_TIME register
#define ATA_XFR_NUM         (0x4B801934) //Data transfer number register
#define ATA_XFR_CNT         (0x4B801938) //Current remaining transfer counter
#define ATA_TBUF_START      (0x4B80193C) //Start address of track buffer 
#define ATA_TBUF_SIZE       (0x4B801940) //Size of track buffer 
#define ATA_SBUF_START      (0x4B801944) //Start address of source buffer
#define ATA_SBUF_SIZE       (0x4B801948) //Size of source buffer
#define ATA_CADDR_TBUR      (0x4B80194C) //Current address of track buffer
#define ATA_CADDR_SBUF      (0x4B801950) //Current address of source buffer
#define ATA_PIO_DTR         (0x4B801954) //16-bit PIO data register
#define ATA_PIO_FED         (0x4B801958) //8-bit PIO device feature/error (command block) register
#define ATA_PIO_SCR         (0x4B80195C) //8-bit PIO device sector count (command block) register
#define ATA_PIO_LLR         (0x4B801960) //8-bit PIO device LBA low (command block) register
#define ATA_PIO_LMR         (0x4B801964) //8-bit PIO device LBA middle (command block) register
#define ATA_PIO_LHR         (0x4B801968) //8-bit PIO LBA high (command block) register
#define ATA_PIO_DVR         (0x4B80196C) //8-bit PIO device (command block) register
#define ATA_PIO_CSD         (0x4B801970) //8-bit PIO device command/status (command block) register
#define ATA_PIO_DAD         (0x4B801974) //8-bit PIO device control/alternate status (control block) register
#define ATA_PIO_READY       (0x4B801978) //ATA_PIO_READY register
#define ATA_PIO_RDATA       (0x4B80197C) //PIO read data register while HOST read from ATA device register
#define BUS_FIFO_STATUS     (0x4B801990) //BUS_FIFO_STATUS  register
#define ATA_FIFO_STATUS     (0x4B801994) //ATA_FIFO_STATUS  register


// chapter9 DMA - jcs
#define DISRC0     (0x4b000000)	//DMA 0 Initial source
#define DISRCC0    (0x4b000004)	//DMA 0 Initial source control
#define DIDST0     (0x4b000008)	//DMA 0 Initial Destination
#define DIDSTC0    (0x4b00000c)	//DMA 0 Initial Destination control
#define DCON0      (0x4b000010)	//DMA 0 Control
#define DSTAT0     (0x4b000014)	//DMA 0 Status (Read Only)
#define DCSRC0     (0x4b000018)	//DMA 0 Current source (Read Only)
#define DCDST0     (0x4b00001c)	//DMA 0 Current destination (Read Only)
#define DMASKTRIG0 (0x4b000020)	//DMA 0 Mask trigger
#define DMAREQSEL0 (0x4b000024)	//DMA 0 Request Selection register

#define DISRC1     (0x4b000100)	//DMA 1 Initial source
#define DISRCC1    (0x4b000104)	//DMA 1 Initial source control
#define DIDST1     (0x4b000108)	//DMA 1 Initial Destination
#define DIDSTC1    (0x4b00010c)	//DMA 1 Initial Destination control
#define DCON1      (0x4b000110)	//DMA 1 Control
#define DSTAT1     (0x4b000114)	//DMA 1 Status (Read Only)
#define DCSRC1     (0x4b000118)	//DMA 1 Current source (Read Only)
#define DCDST1     (0x4b00011c)	//DMA 1 Current destination (Read Only)
#define DMASKTRIG1 (0x4b000120)	//DMA 1 Mask trigger
#define DMAREQSEL1 (0x4b000124)	//DMA 1 Request Selection register

#define DISRC2     (0x4b000200)	//DMA 2 Initial source
#define DISRCC2    (0x4b000204)	//DMA 2 Initial source control
#define DIDST2     (0x4b000208)	//DMA 2 Initial Destination
#define DIDSTC2    (0x4b00020c)	//DMA 2 Initial Destination control
#define DCON2      (0x4b000210)	//DMA 2 Control
#define DSTAT2     (0x4b000214)	//DMA 2 Status (Read Only)
#define DCSRC2     (0x4b000218)	//DMA 2 Current source (Read Only)
#define DCDST2     (0x4b00021c)	//DMA 2 Current destination (Read Only)
#define DMASKTRIG2 (0x4b000220)	//DMA 2 Mask trigger
#define DMAREQSEL2 (0x4b000224)	//DMA 2 Request Selection register

#define DISRC3     (0x4b000300)	//DMA 3 Initial source
#define DISRCC3    (0x4b000304)	//DMA 3 Initial source control
#define DIDST3     (0x4b000308)	//DMA 3 Initial Destination
#define DIDSTC3    (0x4b00030c)	//DMA 3 Initial Destination control
#define DCON3      (0x4b000310)	//DMA 3 Control
#define DSTAT3     (0x4b000314)	//DMA 3 Status (Read Only)
#define DCSRC3     (0x4b000318)	//DMA 3 Current source (Read Only)
#define DCDST3     (0x4b00031c)	//DMA 3 Current destination (Read Only)
#define DMASKTRIG3 (0x4b000320)	//DMA 3 Mask trigger
#define DMAREQSEL3 (0x4b000324)	//DMA 3 Request Selection register

#define DISRC4     (0x4b000400)	//DMA 3 Initial source
#define DISRCC4    (0x4b000404)	//DMA 3 Initial source control
#define DIDST4     (0x4b000408)	//DMA 3 Initial Destination
#define DIDSTC4    (0x4b00040c)	//DMA 3 Initial Destination control
#define DCON4      (0x4b000410)	//DMA 3 Control
#define DSTAT4     (0x4b000414)	//DMA 3 Status (Read Only)
#define DCSRC4     (0x4b000418)	//DMA 3 Current source (Read Only)
#define DCDST4     (0x4b00041c)	//DMA 3 Current destination (Read Only)
#define DMASKTRIG4 (0x4b000420)	//DMA 3 Mask trigger
#define DMAREQSEL4 (0x4b000424)	//DMA 3 Request Selection register

#define DISRC5     (0x4b000500)	//DMA 3 Initial source
#define DISRCC5    (0x4b000504)	//DMA 3 Initial source control
#define DIDST5     (0x4b000508)	//DMA 3 Initial Destination
#define DIDSTC5    (0x4b00050c)	//DMA 3 Initial Destination control
#define DCON5      (0x4b000510)	//DMA 3 Control
#define DSTAT5     (0x4b000514)	//DMA 3 Status (Read Only)
#define DCSRC5     (0x4b000518)	//DMA 3 Current source (Read Only)
#define DCDST5     (0x4b00051c)	//DMA 3 Current destination (Read Only)
#define DMASKTRIG5 (0x4b000520)	//DMA 3 Mask trigger
#define DMAREQSEL5 (0x4b000524)	//DMA 3 Request Selection register

#define DISRC6     (0x4b000600)	//DMA 3 Initial source
#define DISRCC6    (0x4b000604)	//DMA 3 Initial source control
#define DIDST6     (0x4b000608)	//DMA 3 Initial Destination
#define DIDSTC6    (0x4b00060c)	//DMA 3 Initial Destination control
#define DCON6      (0x4b000610)	//DMA 3 Control
#define DSTAT6     (0x4b000614)	//DMA 3 Status (Read Only)
#define DCSRC6     (0x4b000618)	//DMA 3 Current source (Read Only)
#define DCDST6     (0x4b00061c)	//DMA 3 Current destination (Read Only)
#define DMASKTRIG6 (0x4b000620)	//DMA 3 Mask trigger
#define DMAREQSEL6 (0x4b000624)	//DMA 3 Request Selection register

#define DISRC7     (0x4b000700)	//DMA 3 Initial source
#define DISRCC7    (0x4b000704)	//DMA 3 Initial source control
#define DIDST7     (0x4b000708)	//DMA 3 Initial Destination
#define DIDSTC7    (0x4b00070c)	//DMA 3 Initial Destination control
#define DCON7      (0x4b000710)	//DMA 3 Control
#define DSTAT7     (0x4b000714)	//DMA 3 Status (Read Only)
#define DCSRC7     (0x4b000718)	//DMA 3 Current source (Read Only)
#define DCDST7     (0x4b00071c)	//DMA 3 Current destination (Read Only)
#define DMASKTRIG7 (0x4b000720)	//DMA 3 Mask trigger
#define DMAREQSEL7 (0x4b000724)	//DMA 3 Request Selection register 


#define DMA_REG_BASE 	0x4B000000	// added by junon
#define DMA_REG_OFFSET 	0x100

// chapter9 DMA - jcs
#define rDISRC0     (*(volatile unsigned *)0x4b000000)	//DMA 0 Initial source
#define rDISRCC0    (*(volatile unsigned *)0x4b000004)	//DMA 0 Initial source control
#define rDIDST0     (*(volatile unsigned *)0x4b000008)	//DMA 0 Initial Destination
#define rDIDSTC0    (*(volatile unsigned *)0x4b00000c)	//DMA 0 Initial Destination control
#define rDCON0      (*(volatile unsigned *)0x4b000010)	//DMA 0 Control
#define rDSTAT0     (*(volatile unsigned *)0x4b000014)	//DMA 0 Status (Read Only)
#define rDCSRC0     (*(volatile unsigned *)0x4b000018)	//DMA 0 Current source (Read Only)
#define rDCDST0     (*(volatile unsigned *)0x4b00001c)	//DMA 0 Current destination (Read Only)
#define rDMASKTRIG0 (*(volatile unsigned *)0x4b000020)	//DMA 0 Mask trigger
#define rDMAREQSEL0 (*(volatile unsigned *)0x4b000024)	//DMA 0 Request Selection register
#define rDISRC1     (*(volatile unsigned *)0x4b000100)	//DMA 1 Initial source
#define rDISRCC1    (*(volatile unsigned *)0x4b000104)	//DMA 1 Initial source control
#define rDIDST1     (*(volatile unsigned *)0x4b000108)	//DMA 1 Initial Destination
#define rDIDSTC1    (*(volatile unsigned *)0x4b00010c)	//DMA 1 Initial Destination control
#define rDCON1      (*(volatile unsigned *)0x4b000110)	//DMA 1 Control
#define rDSTAT1     (*(volatile unsigned *)0x4b000114)	//DMA 1 Status (Read Only)
#define rDCSRC1     (*(volatile unsigned *)0x4b000118)	//DMA 1 Current source (Read Only)
#define rDCDST1     (*(volatile unsigned *)0x4b00011c)	//DMA 1 Current destination (Read Only)
#define rDMASKTRIG1 (*(volatile unsigned *)0x4b000120)	//DMA 1 Mask trigger
#define rDMAREQSEL1 (*(volatile unsigned *)0x4b000124)	//DMA 1 Request Selection register
#define rDISRC2     (*(volatile unsigned *)0x4b000200)	//DMA 2 Initial source
#define rDISRCC2    (*(volatile unsigned *)0x4b000204)	//DMA 2 Initial source control
#define rDIDST2     (*(volatile unsigned *)0x4b000208)	//DMA 2 Initial Destination
#define rDIDSTC2    (*(volatile unsigned *)0x4b00020c)	//DMA 2 Initial Destination control
#define rDCON2      (*(volatile unsigned int*)0x4b000210)	//DMA 2 Control
#define rDSTAT2     (*(volatile unsigned *)0x4b000214)	//DMA 2 Status (Read Only)
#define rDCSRC2     (*(volatile unsigned *)0x4b000218)	//DMA 2 Current source (Read Only)
#define rDCDST2     (*(volatile unsigned *)0x4b00021c)	//DMA 2 Current destination (Read Only)
#define rDMASKTRIG2 (*(volatile unsigned *)0x4b000220)	//DMA 2 Mask trigger
#define rDMAREQSEL2 (*(volatile unsigned *)0x4b000224)	//DMA 2 Request Selection register
#define rDISRC3     (*(volatile unsigned *)0x4b000300)	//DMA 3 Initial source
#define rDISRCC3    (*(volatile unsigned *)0x4b000304)	//DMA 3 Initial source control
#define rDIDST3     (*(volatile unsigned *)0x4b000308)	//DMA 3 Initial Destination
#define rDIDSTC3    (*(volatile unsigned *)0x4b00030c)	//DMA 3 Initial Destination control
#define rDCON3      (*(volatile unsigned *)0x4b000310)	//DMA 3 Control
#define rDSTAT3     (*(volatile unsigned *)0x4b000314)	//DMA 3 Status (Read Only)
#define rDCSRC3     (*(volatile unsigned *)0x4b000318)	//DMA 3 Current source (Read Only)
#define rDCDST3     (*(volatile unsigned *)0x4b00031c)	//DMA 3 Current destination (Read Only)
#define rDMASKTRIG3 (*(volatile unsigned *)0x4b000320)	//DMA 3 Mask trigger
#define rDMAREQSEL3 (*(volatile unsigned *)0x4b000324)	//DMA 3 Request Selection register
#define rDISRC4     (*(volatile unsigned *)0x4b000400)	//DMA 3 Initial source
#define rDISRCC4    (*(volatile unsigned *)0x4b000404)	//DMA 3 Initial source control
#define rDIDST4     (*(volatile unsigned *)0x4b000408)	//DMA 3 Initial Destination
#define rDIDSTC4    (*(volatile unsigned *)0x4b00040c)	//DMA 3 Initial Destination control
#define rDCON4      (*(volatile unsigned *)0x4b000410)	//DMA 3 Control
#define rDSTAT4     (*(volatile unsigned *)0x4b000414)	//DMA 3 Status (Read Only)
#define rDCSRC4     (*(volatile unsigned *)0x4b000418)	//DMA 3 Current source (Read Only)
#define rDCDST4     (*(volatile unsigned *)0x4b00041c)	//DMA 3 Current destination (Read Only)
#define rDMASKTRIG4 (*(volatile unsigned *)0x4b000420)	//DMA 3 Mask trigger
#define rDMAREQSEL4 (*(volatile unsigned *)0x4b000424)	//DMA 3 Request Selection register
#define rDISRC5     (*(volatile unsigned *)0x4b000500)	//DMA 3 Initial source
#define rDISRCC5    (*(volatile unsigned *)0x4b000504)	//DMA 3 Initial source control
#define rDIDST5     (*(volatile unsigned *)0x4b000508)	//DMA 3 Initial Destination
#define rDIDSTC5    (*(volatile unsigned *)0x4b00050c)	//DMA 3 Initial Destination control
#define rDCON5      (*(volatile unsigned *)0x4b000510)	//DMA 3 Control
#define rDSTAT5     (*(volatile unsigned *)0x4b000514)	//DMA 3 Status (Read Only)
#define rDCSRC5     (*(volatile unsigned *)0x4b000518)	//DMA 3 Current source (Read Only)
#define rDCDST5     (*(volatile unsigned *)0x4b00051c)	//DMA 3 Current destination (Read Only)
#define rDMASKTRIG5 (*(volatile unsigned *)0x4b000520)	//DMA 3 Mask trigger
#define rDMAREQSEL5 (*(volatile unsigned *)0x4b000524)	//DMA 3 Request Selection register
#define rDISRC6     (*(volatile unsigned *)0x4b000600)	//DMA 3 Initial source
#define rDISRCC6    (*(volatile unsigned *)0x4b000604)	//DMA 3 Initial source control
#define rDIDST6     (*(volatile unsigned *)0x4b000608)	//DMA 3 Initial Destination
#define rDIDSTC6    (*(volatile unsigned *)0x4b00060c)	//DMA 3 Initial Destination control
#define rDCON6      (*(volatile unsigned *)0x4b000610)	//DMA 3 Control
#define rDSTAT6     (*(volatile unsigned *)0x4b000614)	//DMA 3 Status (Read Only)
#define rDCSRC6     (*(volatile unsigned *)0x4b000618)	//DMA 3 Current source (Read Only)
#define rDCDST6     (*(volatile unsigned *)0x4b00061c)	//DMA 3 Current destination (Read Only)
#define rDMASKTRIG6 (*(volatile unsigned *)0x4b000620)	//DMA 3 Mask trigger
#define rDMAREQSEL6 (*(volatile unsigned *)0x4b000624)	//DMA 3 Request Selection register
#define rDISRC7     (*(volatile unsigned *)0x4b000700)	//DMA 3 Initial source
#define rDISRCC7    (*(volatile unsigned *)0x4b000704)	//DMA 3 Initial source control
#define rDIDST7     (*(volatile unsigned *)0x4b000708)	//DMA 3 Initial Destination
#define rDIDSTC7    (*(volatile unsigned *)0x4b00070c)	//DMA 3 Initial Destination control
#define rDCON7      (*(volatile unsigned *)0x4b000710)	//DMA 3 Control
#define rDSTAT7     (*(volatile unsigned *)0x4b000714)	//DMA 3 Status (Read Only)
#define rDCSRC7     (*(volatile unsigned *)0x4b000718)	//DMA 3 Current source (Read Only)
#define rDCDST7     (*(volatile unsigned *)0x4b00071c)	//DMA 3 Current destination (Read Only)
#define rDMASKTRIG7 (*(volatile unsigned *)0x4b000720)	//DMA 3 Mask trigger
#define rDMAREQSEL7 (*(volatile unsigned *)0x4b000724)	//DMA 3 Request Selection register 

// chapter10 INTERRUPT - gom
#define rSRCPND		(*(volatile unsigned *)0x4a000000)	//Interrupt request status
#define rINTMOD		(*(volatile unsigned *)0x4a000004)	//Interrupt mode control
#define rINTMSK		(*(volatile unsigned *)0x4a000008)	//Interrupt mask control
#define rINTPND		(*(volatile unsigned *)0x4a000010)	//Interrupt request status
#define rINTOFFSET	(*(volatile unsigned *)0x4a000014)	//Interruot request source offset
#define rSUBSRCPND	(*(volatile unsigned *)0x4a000018)	//Sub source pending
#define rINTSUBMSK	(*(volatile unsigned *)0x4a00001c)	//Interrupt sub mask
#define rPRIORITY_MODE1			(*(volatile unsigned *)0x4a000030)	//Interrupt request status
#define rPRIORITY_UPDATE1		(*(volatile unsigned *)0x4a000034)	//Interrupt mode control
#define rSRCPND2	(*(volatile unsigned *)0x4a000040)	//Interrupt request status
#define rINTMOD2	(*(volatile unsigned *)0x4a000044)	//Interrupt mode control
#define rINTMSK2		(*(volatile unsigned *)0x4a000048)	//Interrupt mask control
#define rINTPND2		(*(volatile unsigned *)0x4a000050)	//Interrupt request status
#define rINTOFFSET2	(*(volatile unsigned *)0x4a000054)	//Interruot request source offset
#define rPRIORITY_MODE2			(*(volatile unsigned *)0x4a000070)	//Interrupt request status
#define rPRIORITY_UPDATE2		(*(volatile unsigned *)0x4a000074)	//Interrupt mode control

// chapter10 INTERRUPT - gom
#define SRCPND		(0x4a000000)	//Interrupt request status
#define INTMOD		(0x4a000004)	//Interrupt mode control
#define INTMSK		(0x4a000008)	//Interrupt mask control
#define INTPND		(0x4a000010)	//Interrupt request status
#define INTOFFSET	(0x4a000014)	//Interruot request source offset
#define SUBSRCPND	(0x4a000018)	//Sub source pending
#define INTSUBMSK	(0x4a00001c)	//Interrupt sub mask
#define PRIORITY_MODE1			(0x4a000030)	//Interrupt request status
#define PRIORITY_UPDATE1		(0x4a000034)	//Interrupt mode control
#define SRCPND2	(0x4a000040)	//Interrupt request status
#define INTMOD2	(0x4a000044)	//Interrupt mode control
#define INTMSK2		(0x4a000048)	//Interrupt mask control
#define INTPND2		(0x4a000050)	//Interrupt request status
#define INTOFFSET2	(0x4a000054)	//Interruot request source offset
#define PRIORITY_MODE2			(0x4a000070)	//Interrupt request status
#define PRIORITY_UPDATE2		(0x4a000074)	//Interrupt mode control

// chapter11 I/O PORT - oh
#define  rGPACON			(*(volatile unsigned *)(0x56000000))	
#define  rGPADAT			(*(volatile unsigned *)(0x56000004))	
#define  rGPBCON			(*(volatile unsigned *)(0x56000010))	
#define  rGPBDAT			(*(volatile unsigned *)(0x56000014))	
#define  rGPBUDP			(*(volatile unsigned *)(0x56000018))	
#define  rGPBSEL			(*(volatile unsigned *)(0x5600001c))	
#define  rGPCCON			(*(volatile unsigned *)(0x56000020))	
#define  rGPCDAT			(*(volatile unsigned *)(0x56000024))	
#define  rGPCUDP			(*(volatile unsigned *)(0x56000028))	
#define  rGPDCON			(*(volatile unsigned *)(0x56000030))	
#define  rGPDDAT			(*(volatile unsigned *)(0x56000034))	
#define  rGPDUDP			(*(volatile unsigned *)(0x56000038))	
#define  rGPECON			(*(volatile unsigned *)(0x56000040))	
#define  rGPEDAT			(*(volatile unsigned *)(0x56000044))	
#define  rGPEUDP			(*(volatile unsigned *)(0x56000048))	
#define  rGPESEL			(*(volatile unsigned *)(0x5600004c))	
#define  rGPFCON			(*(volatile unsigned *)(0x56000050))	
#define  rGPFDAT			(*(volatile unsigned *)(0x56000054))	
#define  rGPFUDP			(*(volatile unsigned *)(0x56000058))	
#define  rGPGCON			(*(volatile unsigned *)(0x56000060))	
#define  rGPGDAT			(*(volatile unsigned *)(0x56000064))	
#define  rGPGUDP			(*(volatile unsigned *)(0x56000068))	
#define  rGPHCON			(*(volatile unsigned *)(0x56000070))	
#define  rGPHDAT			(*(volatile unsigned *)(0x56000074))	
#define  rGPHUDP			(*(volatile unsigned *)(0x56000078))	
#define  rGPJCON			(*(volatile unsigned *)(0x560000d0))	
#define  rGPJDAT				(*(volatile unsigned *)(0x560000d4))	
#define  rGPJUDP			(*(volatile unsigned *)(0x560000d8))	
#define  rGPJSEL				(*(volatile unsigned *)(0x560000dc))	
#define  rGPKCON			(*(volatile unsigned *)(0x560000e0))	
#define  rGPKDAT			(*(volatile unsigned *)(0x560000e4))	
#define  rGPKUDP			(*(volatile unsigned *)(0x560000e8))	
#define  rGPLCON			(*(volatile unsigned *)(0x560000f0))	
#define  rGPLDAT			(*(volatile unsigned *)(0x560000f4))	
#define  rGPLUDP			(*(volatile unsigned *)(0x560000f8))	
#define  rGPLSEL			(*(volatile unsigned *)(0x560000fc))	
#define  rGPMCON			(*(volatile unsigned *)(0x56000100))	
#define  rGPMDAT			(*(volatile unsigned *)(0x56000104))	
#define  rGPMUDP			(*(volatile unsigned *)(0x56000108))	
#define  rMISCCR			(*(volatile unsigned *)(0x56000080))	
#define  rDCLKCON			(*(volatile unsigned *)(0x56000084))	
#define  rEXTINT0			(*(volatile unsigned *)(0x56000088))	
#define  rEXTINT1			(*(volatile unsigned *)(0x5600008c))	
#define  rEXTINT2			(*(volatile unsigned *)(0x56000090))	
#define  rEINTFLT2			(*(volatile unsigned *)(0x5600009c))	
#define  rEINTFLT3			(*(volatile unsigned *)(0x4c6000a0))	
#define  rEINTMASK			(*(volatile unsigned *)(0x560000a4))	
#define  rEINTPEND			(*(volatile unsigned *)(0x560000a8))	
#define  rGSTATUS0			(*(volatile unsigned *)(0x560000ac))	
#define  rGSTATUS1			(*(volatile unsigned *)(0x560000b0))	
#define  rDSC0				(*(volatile unsigned *)(0x560000c0))	
#define  rDSC1				(*(volatile unsigned *)(0x560000c4))	
#define	 rDSC2				(*(volatile unsigned *)(0x560000c8))
#define  rDSC3		    		(*(volatile unsigned *)(0x56000110))	
#define  rPDDMCON			(*(volatile unsigned *)(0x56000114))	
#define  rPDSMCON			(*(volatile unsigned *)(0x56000118))


// chapter11 I/O PORT - oh
#define GPACON			(0x56000000)	
#define GPADAT			(0x56000004)	
#define GPBCON			(0x56000010)	
#define GPBDAT			(0x56000014)	
#define GPBUDP			(0x56000018)	
#define GPBSEL			(0x5600001c)	
#define GPCCON			(0x56000020)	
#define GPCDAT			(0x56000024)	
#define GPCUDP			(0x56000028)	
#define GPDCON			(0x56000030)	
#define GPDDAT			(0x56000034)	
#define GPDUDP			(0x56000038)	
#define GPECON			(0x56000040)	
#define GPEDAT			(0x56000044)	
#define GPEUDP			(0x56000048)	
#define GPESEL			(0x5600004c)	
#define GPFCON			(0x56000050)	
#define GPFDAT			(0x56000054)	
#define GPFUDP			(0x56000058)	
#define GPGCON			(0x56000060)	
#define GPGDAT			(0x56000064)	
#define GPGUDP			(0x56000068)	
#define GPHCON			(0x56000070)	
#define GPHDAT			(0x56000074)	
#define GPHUDP			(0x56000078)	
#define GPJCON			(0x560000d0)	
#define GPJDAT				(0x560000d4)	
#define GPJUDP			(0x560000d8)	
#define GPJSEL				(0x560000dc)	
#define GPKCON			(0x560000e0)	
#define GPKDAT			(0x560000e4)	
#define GPKUDP			(0x560000e8)	
#define GPLCON			(0x560000f0)	
#define GPLDAT			(0x560000f4)	
#define GPLUDP			(0x560000f8)	
#define GPLSEL			(0x560000fc)	
#define GPMCON			(0x56000100)	
#define GPMDAT			(0x56000104)	
#define GPMUDP			(0x56000108)	

#define MISCCR			(0x56000080)	
#define DCLKCON			(0x56000084)	
#define EXTINT0			(0x56000088)	
#define EXTINT1			(0x5600008c)	
#define EXTINT2			(0x56000090)	
#define EINTFLT2			(0x5600009c)	
#define EINTFLT3			(0x4c6000a0)	
#define EINTMASK			(0x560000a4)	
#define EINTPEND			(0x560000a8)	
#define GSTATUS0			(0x560000ac)	
#define GSTATUS1			(0x560000b0)	
#define DSC0				(0x560000c0)	
#define DSC1				(0x560000c4)	
#define	DSC2				(0x560000c8)
#define DSC3		    		(0x56000110)	
#define PDDMCON			(0x56000114)	
#define PDSMCON			(0x56000118)

// chapter12 WATCH DOG TIMER - junon
#define WTCON		(0x53000000)	//Watch-dog timer mode
#define WTDAT		(0x53000004)	//Watch-dog timer data
#define WTCNT		(0x53000008)	//Watch-dog timer count


// chapter13 PWM TIMER - jcs
#define TCFG0  	(0x51000000)	//Configures the two 8-bit presclers
#define TCFG1  	(0x51000004)	//5-MUX & DMA mode selecton
#define TCON   	(0x51000008)	//Timer control
#define TCNTB0 	(0x5100000c)	//Timer 0 count buffer 
#define TCMPB0 	(0x51000010)	//Timer 0 compare buffer 
#define TCNTO0 	(0x51000014)	//Timer 0 count observation 
#define TCNTB1 	(0x51000018)	//Timer 1 count buffer 
#define TCMPB1 	(0x5100001c)	//Timer 1 compare buffer 
#define TCNTO1 	(0x51000020)	//Timer 1 count observation 
#define TCNTB2 	(0x51000024)	//Timer 2 count buffer 
#define TCMPB2 	(0x51000028)	//Timer 2 compare buffer 
#define TCNTO2 	(0x5100002c)	//Timer 2 count observation 
#define TCNTB3 	(0x51000030)	//Timer 3 count buffer 
#define TCMPB3 	(0x51000034)	//Timer 3 compare buffer 
#define TCNTO3 	(0x51000038)	//Timer 3 count observation 
#define TCNTB4 	(0x5100003c)	//Timer 4 count buffer 
#define TCNTO4 	(0x51000040)	//Timer 4 count observation
// chapter13 PWM TIMER - jcs
#define rTCFG0  	(*(volatile unsigned *)0x51000000)	//Configures the two 8-bit presclers
#define rTCFG1  	(*(volatile unsigned *)0x51000004)	//5-MUX & DMA mode selecton
#define rTCON   	(*(volatile unsigned *)0x51000008)	//Timer control
#define rTCNTB0 	(*(volatile unsigned *)0x5100000c)	//Timer 0 count buffer 
#define rTCMPB0 	(*(volatile unsigned *)0x51000010)	//Timer 0 compare buffer 
#define rTCNTO0 	(*(volatile unsigned *)0x51000014)	//Timer 0 count observation 
#define rTCNTB1 	(*(volatile unsigned *)0x51000018)	//Timer 1 count buffer 
#define rTCMPB1 	(*(volatile unsigned *)0x5100001c)	//Timer 1 compare buffer 
#define rTCNTO1 	(*(volatile unsigned *)0x51000020)	//Timer 1 count observation 
#define rTCNTB2 	(*(volatile unsigned *)0x51000024)	//Timer 2 count buffer 
#define rTCMPB2 	(*(volatile unsigned *)0x51000028)	//Timer 2 compare buffer 
#define rTCNTO2 	(*(volatile unsigned *)0x5100002c)	//Timer 2 count observation 
#define rTCNTB3 	(*(volatile unsigned *)0x51000030)	//Timer 3 count buffer 
#define rTCMPB3 	(*(volatile unsigned *)0x51000034)	//Timer 3 compare buffer 
#define rTCNTO3 	(*(volatile unsigned *)0x51000038)	//Timer 3 count observation 
#define rTCNTB4 	(*(volatile unsigned *)0x5100003c)	//Timer 4 count buffer 
#define rTCNTO4 	(*(volatile unsigned *)0x51000040)	//Timer 4 count observation


// chapter14 RTC - oh

#define RTCCON		(0x57000040)	//RTC control
#define TICNT0		(0x57000044)	//Tick time count register 0
#define TICNT1		(0x5700004c)	//Tick time count register 1
#define TICNT2		(0x57000048)		//Tick time count register 2
#define RTCALM		(0x57000050)	//RTC alarm control
#define ALMSEC		(0x57000054)	//Alarm second
#define ALMMIN		(0x57000058)	//Alarm minute
#define ALMHOUR	(0x5700005c)	//Alarm Hour
#define ALMDATE	(0x57000060)	//Alarm date  // edited by junon
#define ALMMON		(0x57000064)	//Alarm month
#define ALMYEAR	(0x57000068)	//Alarm year
#define RTCRST		(0x5700006c)	//RTC round reset
#define BCDSEC		(0x57000070)	//BCD second
#define BCDMIN		(0x57000074)	//BCD minute
#define BCDHOUR	(0x57000078)	//BCD hour
#define BCDDATE	(0x5700007c)	//BCD date  //edited by junon
#define BCDDAY		(0x57000080)	//BCD day   //edited by junon
#define BCDMON		(0x57000084)	//BCD month
#define BCDYEAR	(0x57000088)	//BCD year
#define TICKCNT		(0x57000090)		//Tick count



// chapter15 UART - gom
#define ULCON0     (0x50000000)	//UART 0 Line control
#define UCON0      (0x50000004)	//UART 0 Control
#define UFCON0     (0x50000008)	//UART 0 FIFO control
#define UMCON0     (0x5000000c)	//UART 0 Modem control
#define UTRSTAT0   (0x50000010)	//UART 0 Tx/Rx status
#define UERSTAT0   (0x50000014)	//UART 0 Rx error status
#define UFSTAT0    (0x50000018)	//UART 0 FIFO status
#define UMSTAT0    (0x5000001c)	//UART 0 Modem status
#define UBRDIV0    (0x50000028)	//UART 0 Baud rate divisor
#define UDIVSLOT0  (0x5000002C)	//UART 0 Baud rate divisor
#define ULCON1     (0x50004000)	//UART 1 Line control
#define UCON1      (0x50004004)	//UART 1 Control
#define UFCON1     (0x50004008)	//UART 1 FIFO control
#define UMCON1     (0x5000400c)	//UART 1 Modem control
#define UTRSTAT1   (0x50004010)	//UART 1 Tx/Rx status
#define UERSTAT1   (0x50004014)	//UART 1 Rx error status
#define UFSTAT1    (0x50004018)	//UART 1 FIFO status
#define UMSTAT1    (0x5000401c)	//UART 1 Modem status
#define UBRDIV1    (0x50004028)	//UART 1 Baud rate divisor
#define UDIVSLOT1  (0x5000402C)	//UART 1 Baud rate divisor
#define ULCON2     (0x50008000)	//UART 2 Line control
#define UCON2      (0x50008004)	//UART 2 Control
#define UFCON2     (0x50008008)	//UART 2 FIFO control
#define UMCON2     (0x5000800c)	//UART 2 Modem control
#define UTRSTAT2   (0x50008010)	//UART 2 Tx/Rx status
#define UERSTAT2   (0x50008014)	//UART 2 Rx error status
#define UFSTAT2    (0x50008018)	//UART 2 FIFO status
#define UMSTAT2    (0x5000801c)	//UART 2 Modem status
#define UBRDIV2    (0x50008028)	//UART 2 Baud rate divisor
#define UDIVSLOT2  (0x5000802C)	//UART 2 Baud rate divisor
#define ULCON3     (0x5000C000)	//UART 2 Line control
#define UCON3      (0x5000C004)	//UART 3 Control
#define UFCON3     (0x5000C008)	//UART 3 FIFO control
#define UMCON3     (0x5000C00c)	//UART 3 Modem control
#define UTRSTAT3   (0x5000C010)	//UART 3 Tx/Rx status
#define UERSTAT3   (0x5000C014)	//UART 3 Rx error status
#define UFSTAT3    (0x5000C018)	//UART 3 FIFO status
#define UMSTAT3    (0x5000C01c)	//UART 3 Modem status
#define UBRDIV3    (0x5000C028)	//UART 3 Baud rate divisor
#define UDIVSLOT3  (0x5000C02C)	//UART 3 Baud rate divisor

#ifdef __BIG_ENDIAN
#define UTXH0      (0x50000023)	//UART 0 Transmission Hold
#define URXH0      (0x50000027)	//UART 0 Receive buffer
#define UTXH1      (0x50004023)	//UART 1 Transmission Hold
#define URXH1      (0x50004027)	//UART 1 Receive buffer
#define UTXH2      (0x50008023)	//UART 2 Transmission Hold
#define URXH2      (0x50008027)	//UART 2 Receive buffer
#define UTXH3      (0x5000C023)	//UART 3 Transmission Hold
#define URXH3      (0x5000C027)	//UART 3 Receive buffer
#define WrUTXH0(ch) (0x50000023)=(unsigned char)(ch)
#define RdURXH0()   (0x50000027)
#define WrUTXH1(ch) (0x50004023)=(unsigned char)(ch)
#define RdURXH1()   (0x50004027)
#define WrUTXH2(ch) (0x50008023)=(unsigned char)(ch)
#define RdURXH2()   (0x50008027)
#define WrUTXH3(ch) (0x5000C023)=(unsigned char)(ch)
#define RdURXH3()   (0x5000C027)
#define UTXH0       (0x50000020+3)  //Byte_access address by DMA
#define URXH0       (0x50000024+3)
#define UTXH1       (0x50004020+3)
#define URXH1       (0x50004024+3)
#define UTXH2       (0x50008020+3)
#define URXH2       (0x50008024+3)
#define UTXH3       (0x5000C020+3)
#define URXH3       (0x5000C024+3)

#else //Little Endian
#define UTXH0		(0x50000020)	//UART 0 Transmission Hold
#define URXH0		(0x50000024)	//UART 0 Receive buffer
#define UTXH1		(0x50004020)	//UART 1 Transmission Hold
#define URXH1		(0x50004024)	//UART 1 Receive buffer
#define UTXH2		(0x50008020)	//UART 2 Transmission Hold
#define URXH2		(0x50008024)	//UART 2 Receive buffer
#define UTXH3		(0x5000C020)	//UART 3 Transmission Hold
#define URXH3		(0x5000C024)	//UART 3 Receive buffer
#define WrUTXH0(ch) (0x50000020)=(unsigned char)(ch)
#define RdURXH0()   (0x50000024)
#define WrUTXH1(ch) (0x50004020)=(unsigned char)(ch)
#define RdURXH1()   (0x50004024)
#define WrUTXH2(ch) (0x50008020)=(unsigned char)(ch)
#define RdURXH2()   (0x50008024)
#define WrUTXH3(ch) (0x5000C020)=(unsigned char)(ch)
#define RdURXH3()   (0x5000C024)
#define UTXH0       (0x50000020)    //Byte_access address by DMA
#define URXH0       (0x50000024)
#define UTXH1       (0x50004020)
#define URXH1       (0x50004024)
#define UTXH2       (0x50008020)
#define URXH2       (0x50008024)
#define UTXH3       (0x5000C020)
#define URXH3       (0x5000C024)
#endif

#define UART_REG_BASE 	0x50000000	// added by junon
#define UART_REG_OFFSET 	0x4000


#define OFS_ULCON     (ULCON0-ULCON0)  //UART Line control
#define OFS_UCON      (UCON0-ULCON0)   //UART Control
#define OFS_UFCON     (UFCON0-ULCON0)  //UART FIFO control
#define OFS_UMCON     (UMCON0-ULCON0)  //UART Modem control
#define OFS_UTRSTAT   (UTRSTAT0-ULCON0)//UART Tx/Rx status
#define OFS_UERSTAT   (UERSTAT0-ULCON0)//UART Rx error status
#define OFS_UFSTAT    (UFSTAT0-ULCON0) //UART FIFO status
#define OFS_UMSTAT    (UMSTAT0-ULCON0) //UART Modem status
#define OFS_UBRDIV    (UBRDIV0-ULCON0) //UART Baud rate divisor
#define OFS_UTXH      (UTXH0-ULCON0)   //UART Transmission Hold
#define OFS_URXH      (URXH0-ULCON0)   //UART Receive buffer
#define OFS_UDIVSLOT	(UDIVSLOT0-ULCON0)

// chapter16 USB HOST 1.1 - cha
#define HcRevision            (0x49000000)	//Control and status group
#define HcControl             (0x49000004)	//Control and status group
#define HcCommonStatus        (0x49000008)	//Control and status group
#define HcInterruptStatus     (0x4900000C)	//Control and status group
#define HcInterruptEnable     (0x49000010)	//Control and status group
#define HcInterruptDisable    (0x49000014)	//Control and status group
#define HcHCCA                (0x49000018)	//Memory pointer group
#define HcPeridCuttentED      (0x4900001C)	//Memory pointer group
#define HcControlHeadED       (0x49000020)	//Memory pointer group
#define HcControlCurrentED    (0x49000024)	//Memory pointer group
#define HcBulkHeadED          (0x49000028)	//Memory pointer group
#define HcBulkCurrentED       (0x4900002C)	//Memory pointer group
#define HcDoneHead            (0x49000030)	//Memory pointer group
#define HcRmlnterval          (0x49000034)	//frame counter group
#define HcFmRemaining         (0x49000038)	//frame counter group
#define HcFmNumber            (0x4900003C)	//frame counter group
#define HcPeridicStart        (0x49000040)	//frame counter group
#define HcLSThreshold         (0x49000044)	//frame counter group
#define HcRhDescriptorA       (0x49000048)	//Root hub group
#define HcRhDescriptorB       (0x4900004C)	//Root hub group
#define HcRStatus             (0x49000050)	//Root hub group
#define HcRhPortStatus1       (0x49000054)	//Root hub group
#define HcRhPortStatus2       (0x49000058)	//Root hub group


// chapter17 USB DEVICE 2.0 - cha
#define IR     	(0x49800000)	//Index Register
#define EIR        (0x49800004)	//Endpoint Interrupt Register
#define EIER       (0x49800008)	//Endpoint Interrupt Enable Register
#define FAR        (0x4980000C)	//Function Address Register 
#define FNR        (0x49800010)	//Frame Number Register
#define EDR    	(0x49800014) //Endpoint Direction Register
#define TR    		(0x49800018)	//Test Register
#define SSR    	(0x4980001C)	//System Status Register
#define SCR        (0x49800020)	//System Control Register
#define EP0SR      (0x49800024)	//EP0 Status Register
#define EP0CR      (0x49800028)	//EP0 Control Register
#define EP0BR      (0x49800060)	//EP0 Buffer Register
#define EP1BR      (0x49800064)	//EP1 Buffer Register
#define EP2BR      (0x49800068)	//EP2 Buffer Register
#define EP3BR      (0x4980006C)	//EP3 Buffer Register
#define EP4BR      (0x49800070)	//EP4 Buffer Register
#define EP5BR      (0x49800074)	//EP5 Buffer Register
#define EP6BR      (0x49800078)	//EP6 Buffer Register
#define EP7BR      (0x4980007C)	//EP7 Buffer Register
#define EP8BR      (0x49800080)	//EP8 Buffer Register
#define FCON       (0x49800100) //Burst FIFO-DMA Control
#define FSTAT      (0x49800104)	//Burst FIFO status
#define ESR  	    (0x4980002C)	//Endpoints Status Register
#define ECR 		(0x49800030)	//Endpoints Control Register
#define BRCR 		(0x49800034)	//Byte Read Count Register
#define BWCR       (0x49800038)	//Byte Write Count Register
#define MPR        (0x4980003C)	//Max Packet Register
#define DCR        (0x49800040)	//DMA Control Register
#define DTCR       (0x49800044)	//DMA Transfer Counter Register
#define DFCR       (0x49800048)	//DMA FIFO Counter Register
#define DTTCR1     (0x4980004C)	//DMA Total Transfer Counter1 Register
#define DTTCR2     (0x49800050)	//DMA Total Transfer Counter2 Register
#define MICR      	(0x49800054)	//Master Interface Control Register
#define MBAR     	(0x49800088)	//Memory Base Address Register
#define MCAR     	(0x4980008C)  //Memory Current Address Register


// chapter18 IIC - cha
#define IICCON		(0x54000000)	//IIC control
#define IICSTAT	(0x54000004)	//IIC control/status
#define IICADD		(0x54000008)	//IIC address
#define IICDS		(0x5400000c)	//IIC transmit/receive data shift
#define IICLC		(0x54000010)	//IIC-Bus multi-master line control register

#define IICCON1	(0x54000100)	//IIC control
#define IICSTAT1	(0x54000104)	//IIC control/status
#define IICADD1	(0x54000108)	//IIC address
#define IICDS1		(0x5400010c)	//IIC transmit/receive data shift
#define IICLC1		(0x54000110)	//IIC-Bus multi-master line control register


// chapter19 2D - jcs 


#define G2D_BASE_TEMP			0x4D408000 //temporarily used for the IP verfication of 2D v2.0

#define	G2D_CONTROL        (G2D_BASE_TEMP+0x00)
#define	G2D_INTEN          (G2D_BASE_TEMP+0x04)
#define	G2D_FIFO_INTC      (G2D_BASE_TEMP+0x08)
#define	G2D_INTC_PEND		(G2D_BASE_TEMP+0x0c)
#define	G2D_FIFO_STAT       (G2D_BASE_TEMP+0x10)

#define	G2D_CMDR0                  (G2D_BASE_TEMP+0x100)
#define	G2D_CMDR1                   (G2D_BASE_TEMP+0x104)
#define	G2D_CMDR2                   (G2D_BASE_TEMP+0x108)
#define	G2D_CMDR3                   (G2D_BASE_TEMP+0x10c)
#define	G2D_CMDR4                   (G2D_BASE_TEMP+0x110)
#define	G2D_CMDR5                   (G2D_BASE_TEMP+0x114)
#define	G2D_CMDR6                   (G2D_BASE_TEMP+0x118)	//Reserved
#define	G2D_CMDR7                   (G2D_BASE_TEMP+0x11c)


#define	G2D_SRC_RES				(G2D_BASE_TEMP+0x200)
#define	G2D_SRC_HORI_RES			(G2D_BASE_TEMP+0x204)
#define	G2D_SRC_VERT_RES			(G2D_BASE_TEMP+0x208)

#define	G2D_SC_RES					(G2D_BASE_TEMP+0x210)		//SC_RES_REG
#define	G2D_SC_HORI_RES			(G2D_BASE_TEMP+0x214)		//SC_HORI_RES _REG
#define	G2D_SC_VERT_RES			(G2D_BASE_TEMP+0x218) 	//SC_VERT_RES _REG

//---------
#define	G2D_CW_LT					(G2D_BASE_TEMP+0x220)
#define	G2D_CW_LT_X	    	   	(G2D_BASE_TEMP+0x224)
#define	G2D_CW_LT_Y   		    	(G2D_BASE_TEMP+0x228)
#define	G2D_CW_RB   		    	(G2D_BASE_TEMP+0x230)
#define	G2D_CW_RB_X   				(G2D_BASE_TEMP+0x234)
#define	G2D_CW_RB_Y   				(G2D_BASE_TEMP+0x238)

#define	G2D_COORD0              	(G2D_BASE_TEMP+0x300)
#define	G2D_COORD0_X               (G2D_BASE_TEMP+0x304)
#define	G2D_COORD0_Y               (G2D_BASE_TEMP+0x308)
#define	G2D_COORD1              	(G2D_BASE_TEMP+0x310)
#define	G2D_COORD1_X               (G2D_BASE_TEMP+0x314)
#define	G2D_COORD1_Y               (G2D_BASE_TEMP+0x318)
#define	G2D_COORD2              	(G2D_BASE_TEMP+0x320)
#define	G2D_COORD2_X               (G2D_BASE_TEMP+0x324)
#define	G2D_COORD2_Y               (G2D_BASE_TEMP+0x328)
#define	G2D_COORD3              	(G2D_BASE_TEMP+0x330)
#define	G2D_COORD3_X               (G2D_BASE_TEMP+0x334)
#define	G2D_COORD3_Y               (G2D_BASE_TEMP+0x338)

#define	G2D_ROT_OC              	(G2D_BASE_TEMP+0x340)
#define	G2D_ROT_OC_X                (G2D_BASE_TEMP+0x344)
#define	G2D_ROT_OC_Y                (G2D_BASE_TEMP+0x348)
#define	G2D_ROTATE             	  (G2D_BASE_TEMP+0x34c)

#define	G2D_ENDIAN    			 	(G2D_BASE_TEMP+0x350)

#define	G2D_X_INCR                  (G2D_BASE_TEMP+0x400)
#define	G2D_Y_INCR                  (G2D_BASE_TEMP+0x404)

#define	G2D_ROP                 	(G2D_BASE_TEMP+0x410)
#define	G2D_ALPHA                   (G2D_BASE_TEMP+0x420)

#define	G2D_FG_COLOR                (G2D_BASE_TEMP+0x500)
#define	G2D_BG_COLOR                (G2D_BASE_TEMP+0x504)
#define	G2D_BS_COLOR                (G2D_BASE_TEMP+0x508)


#define	G2D_SRC_COLOR_MODE                (G2D_BASE_TEMP+0x510)
#define	G2D_DEST_COLOR_MODE                (G2D_BASE_TEMP+0x514)

#define	G2D_PATTERN_ADDR            (G2D_BASE_TEMP+0x600)
#define	G2D_PATOFF		          	(G2D_BASE_TEMP+0x700)
#define	G2D_PATOFF_X               (G2D_BASE_TEMP+0x704)
#define	G2D_PATOFF_Y               (G2D_BASE_TEMP+0x708)                                      																																								
#define	G2D_COLORKEY_CNTL           (G2D_BASE_TEMP+0x720)	//STENCIL_CNTL_REG	
#define	G2D_COLORKEY_DR_MIN         (G2D_BASE_TEMP+0x724)	//STENCIL_DR_MIN_REG
#define	G2D_COLORKEY_DR_MAX         (G2D_BASE_TEMP+0x728)	//STENCIL_DR_MAX_REG


#define	G2D_SRC_BASE_ADDR         (G2D_BASE_TEMP+0x730)
#define	G2D_DEST_BASE_ADDR       (G2D_BASE_TEMP+0x734) //mostly frame buffer address



// chapter20 HS_SPI - cha
#define CH_CFG0  		(0x52000000)	//SPI configuration
#define CLK_CFG0  		(0x52000004)	//Clock configuration
#define MODE_CFG0  	(0x52000008)	//SPI FIFO control
#define SLAVE_SEL0  	(0x5200000C)	//Slave selection
#define SPI_INT_EN0  	(0x52000010)	//SPI interrupt enable
#define SPI_STATUS0 	(0x52000014)	//SPI status
#define SPI_TX_DATA0  	(0x52000018)	//SPI TX data
#define SPI_RX_DATA0 	(0x5200001C)	//SPI RX data
#define PACKET_CNT0  	(0x52000020)	//count how many data master gets
#define PENDING_CLR0  	(0x52000024)	//Pending clear

#define CH_CFG1  		(0x59000000)	//SPI configuration
#define CLK_CFG1  		(0x59000004)	//Clock configuration
#define MODE_CFG1  	(0x59000008)	//SPI FIFO control
#define SLAVE_SEL1  	(0x5900000C)	//Slave selection
#define SPI_INT_EN1  	(0x59000010)	//SPI interrupt enable
#define SPI_STATUS1 	(0x59000014)	//SPI status
#define SPI_TX_DATA1  	(0x59000018)	//SPI TX data
#define SPI_RX_DATA1 	(0x5900001C)	//SPI RX data
#define PACKET_CNT1  	(0x59000020)	//count how many data master gets
#define PENDING_CLR1  	(0x59000024)	//Pending clear

// chapter21 TFT LCD CONTROLLER - oh
#define VIDCON0		(0x4c800000)	//VIDEO CONTROL REGTISTER 0
#define VIDCON1		(0x4c800004)	//VIDEO CONTROL REGTISTER 1
#define VIDTCON0		(0x4c800008)	//VIDEO CONTROL REGTISTER 0
#define VIDTCON1		(0x4c80000C)	//VIDEO TIME CONTROL REGTISTER 1
#define VIDTCON2		(0x4c800010)	//VIDEO TIME CONTROL REGTISTER 2
#define WINCON0		(0x4c800014)	//WINDOW CONTROL REGTISTER 0
#define WINCON1		(0x4c800018)	//WINDOW CONTROL REGTISTER 1
#define VIDOSD0A		(0x4c800028)	//VIDEO WIDOW 0'S POSITION CONTROL REGTISTER 
#define VIDOSD0B		(0x4c80002C)	//VIDEO WIDOW 0'S POSITION CONTROL REGTISTER 
#define VIDOSD0C		(0x4c800030)	//VIDEO WIDOW 0'S POSITION CONTROL REGTISTER 
#define VIDOSD1A		(0x4c800034)	//VIDEO WIDOW 1'S POSITION CONTROL REGTISTER 
#define VIDOSD1B		(0x4c800038)	//VIDEO WIDOW 1'S POSITION CONTROL REGTISTER 
#define VIDOSD1C		(0x4c80003C)	//VIDEO WIDOW 1'S POSITION CONTROL REGTISTER 
#define VIDW00ADD0B0	(0x4c800064)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW00ADD0B1	(0x4c800068)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW01ADD0		(0x4c80006C)	//WIDOW 1'S BUFFER START ADDR,
#define VIDW00ADD1B0	(0x4c80007C)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW00ADD1B1	(0x4c800080)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW01ADD1		(0x4c800084)	//WIDOW 1'S BUFFER START ADDR,
#define VIDW00ADD2B0	(0x4c800094)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW00ADD2B1	(0x4c800098)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW01ADD2		(0x4c80009C)	//WIDOW 1'S BUFFER START ADDR,
#define VIDINTCON		(0x4c8000AC)	//INDICATE THE VIDEO INTER. CONTROL
#define W1KEYCON0		(0x4c8000B0)	//COLOR KEY CONTROL REG.
#define W1KEYCON1		(0x4c8000B4)	//COLOR KEY CONTROL REG.
#define W2KEYCON0		(0x4c8000B8)	//COLOR KEY CONTROL REG.
#define W2KEYCON1		(0x4c8000BC)	//COLOR KEY CONTROL REG.
#define W3KEYCON0		(0x4c8000C0)	//COLOR KEY CONTROL REG.
#define W3KEYCON1		(0x4c8000C4)	//COLOR KEY CONTROL REG.
#define W4KEYCON0		(0x4c8000C8)	//COLOR KEY CONTROL REG.
#define W4KEYCON1		(0x4c8000CC)	//COLOR KEY CONTROL REG.
#define WIN0MAP		(0x4c8000D0)	//WINDOW COLOR CONTROL
#define WIN1MAP		(0x4c8000D4)	//WINDOW COLOR CONTROL
#define WPALCON		(0x4c8000E4)	//WINDOW PALLETTE CONTROL
#define SYSIFCON0		(0x4c800130)	//SYSTEM INTERFACE MAIN LDI
#define SYSIFCON1		(0x4c800134)	//SYSTEM INTERFACE SUB LDI
#define DITHMODE1		(0x4c800138)	//DITHERING MODE
#define SIFCCON0		(0x4c80013C)	//SYSTEM INTERFACE COMMAND CONTROL
#define SIFCCON1		(0x4c800140)	//SYSTEM IF COMMAND DATA WRITE CONTROL
#define SIFCCON2		(0x4c800144)	//SYSTEM IF COMMAND DATA READ CONTROL
#define CPUTRIGCON1	(0x4c80015C)	//CPU TRIGGER SOURCE MASK
#define CPUTRIGCON2	(0x4c800160)	//SOFTWARE BSED TRIGGER CONTROL
#define VIDW00ADD0B1	(0x4c800068)	//WIDOW 0'S BUFFER START ADDR,
#define VIDW01ADD0		(0x4c80006C)	//WIDOW 1'S BUFFER START ADDR,

#define WIN0_PALETTE_START		(0x4c800400)
#define WIN1_PALETTE_START		(0x4c800800)


// chapter22 CSTN CONTROLLER - oh
#define LCDCON1    (0x4d000000)	//LCD control 1
#define LCDCON2    (0x4d000004)	//LCD control 2
#define LCDCON3    (0x4d000008)	//LCD control 3
#define LCDCON4    (0x4d00000c)	//LCD control 4
#define LCDCON5    (0x4d000010)	//LCD control 5
#define LCDSADDR1  (0x4d000014)	//STN/TFT Frame buffer start address 1
#define LCDSADDR2  (0x4d000018)	//STN/TFT Frame buffer start address 2
#define LCDSADDR3  (0x4d00001c)	//STN/TFT Virtual screen address set
#define REDLUT     (0x4d000020)	//STN : RED LOOKUP TABLE REGISTER
#define GREENLUT   (0x4d000024)	//STN Green lookup table 
#define BLUELUT    (0x4d000028)	//STN Blue lookup table
#define DITHMODE   (0x4d00004c)	//STN Dithering mode
//#define TPAL      (0x4d000050)	//TFT Temporary palette
#define LCDINTPND  (0x4d000024)	//LCD Interrupt pending
#define LCDSRCPND  (0x4d000028)	//LCD Interrupt source
#define LCDINTMSK  (0x4d00002c)	//LCD Interrupt mask


// chapter23 Camera Interface - jcs
#define CISRCFMT		(0x4D800000) //Input Source Format        
#define CIWDOFST		(0x4D800004) //Window offset       
#define CIGCTRL		(0x4D800008) //Global control        
//#define CIFCTRL1           (0x4D80000C) //flash control 1
//#define CIFCTRL2           (0x4D800010) //flash control 2
#define CIDOWSFT2		(0x4D800014) //Window option 2
#define CICOYSA1		(0x4D800018) //Y1 frame start address for codec DMA      
#define CICOYSA2		(0x4D80001C) //Y2 frame start address for codec DMA       
#define CICOYSA3		(0x4D800020) //Y3 frame start address for codec DMA        
#define CICOYSA4		(0x4D800024) //Y4 frame start address for codec DMA          
#define CICOCBSA1		(0x4D800028) //Cb1 frame start address for codec DMA 
#define CICOCBSA2		(0x4D80002C) //Cb2 frame start address for codec DMA        
#define CICOCBSA3		(0x4D800030) //Cb3 frame start address for codec DMA           
#define CICOCBSA4		(0x4D800034) //Cb4 frame start address for codec DMA   
#define CICOCRSA1		(0x4D800038) //Cr1 frame start address for codec DMA
#define CICOCRSA2		(0x4D80003C) //Cr2 frame start address for codec DMA
#define CICOCRSA3		(0x4D800040) //Cr3 frame start address for codec DMA
#define CICOCRSA4		(0x4D800044) //Cr4 frame start address for codec DMA
#define CICOTRGFMT		(0x4D800048) //Target image format of codex DMA
#define CICOCTRL		(0x4D80004C) //Codec DMA comtrol        
#define CICOSCPRERATIO	(0x4D800050) //Codec pre-scaler ratio control      
#define CICOSCPREDST	(0x4D800054) //Codec pre-scaler desitination format
#define CICOSCCTRL		(0x4D800058) //Codec main-scaler control
#define CICOTAREA		(0x4D80005C) //Codec pre-scaler desination format
#define CICOSTATUS		(0x4D800064) //Codec path status
#define CIPRCLRSA1		(0x4D80006C) //RGB 1st frame start address for preview DMA
#define CIPRCLRSA2		(0x4D800070) //RGB 1st frame start address for preview DMA
#define CIPRCLRSA3		(0x4D800074) //RGB 1st frame start address for preview DMA
#define CIPRCLRSA4		(0x4D800078) //RGB 1st frame start address for preview DMA
#define CIPRTRGFMT		(0x4D80007C) //Target image format of Preview DMA
#define CIPRCTRL		(0x4D800080) //Codec DMA comtrol        
#define CIPRSCPRERATIO	(0x4D800084) //Codec pre-scaler ratio control      
#define CIPRSCPREDST	(0x4D800088) //Codec pre-scaler desitination format
#define CIPRSCCTRL		(0x4D80008C) //Codec main-scaler control
#define CIPRTAREA		(0x4D800090) //Codec pre-scaler desination format
#define CIPRSTATUS		(0x4D800098) //Codec path status
#define CIIMGCPT		(0x4D8000A0) //Imahe capture enable command
#define CICOCPTSEQ		(0x4D8000A4) //Codec dma capture sequence related
#define CICOSCOS		(0x4D8000A8) //Codec scan line offset related
#define CIPRSCOS		(0x4D8000Ac) //Preview scan line offset related
#define CIIMGEFF		(0x4D8000B0) //Imahe Effects related
#define CIMSYSA		(0x4D8000B4) //MSDMA Y start address related
#define CIMSCBSA		(0x4D8000B8) //MSDMA Cb start address related
#define CIMSCRSA		(0x4D8000BC) //MSDMA Cr start address related
#define CIMSYEND		(0x4D8000C0) //MSDMA Y end address related
#define CIMSCBEND		(0x4D8000C4) //MSDMA Cb end address related
#define CIMSCREND		(0x4D8000C8) //MSDMA Cr end address related
#define CIMSYOFF		(0x4D8000CC) //MSDMA Y offset related
#define CIMSCBOFF		(0x4D8000D0) //MSDMA Cb offset related
#define CIMSCROFF		(0x4D8000D4) //MSDMA Cr offset related
#define CIMSWIDTH		(0x4D8000D8) //MSDMA source image width related
#define CIMSCTRL		(0x4D8000DC) //MSDMA cotrol


// chapter24 ADC - gom
#define ADCCON		(0x58000000)	//ADC control
#define ADCTSC		(0x58000004)	//ADC touch screen control
#define ADCDLY		(0x58000008)	//ADC start or Interval Delay
#define ADCDAT0	(0x5800000c)	//ADC conversion data 0
#define ADCDAT1	(0x58000010)	//ADC conversion data 1
#define ADCUPDN	(0x58000014)	//Stylus Up/Down interrupt status
#define ADCMUX		(0x58000018)	//Stylus Up/Down interrupt status


// chapter26 IIS Multi Audio interface(address is compatible with 2443)- dongjin
#define IISCON  	(0x55000000)	//IIS Control
#define IISMOD  	(0x55000004)	//IIS Mode
#define IISFIC  	(0x55000008)	//IIS FIFO control
#define IISPSR  	(0x5500000c)	//IIS clock divider control
#define IISTXD  	(0x55000010)	//IIS tracsmit data
#define IISRXD  	(0x55000014)	//IIS recelve data

#define IISCON0  	(0x55000000)	//IIS Control
#define IISMOD0  	(0x55000004)	//IIS Mode
#define IISFIC0  	(0x55000008)	//IIS FIFO control
#define IISPSR0  	(0x5500000c)	//IIS clock divider control
#define IISTXD0  	(0x55000010)	//IIS tracsmit data
#define IISRXD0  	(0x55000014)	//IIS recelve data

// chapter25 IIS(added)- dongjin
#define IISCON1  	(0x55000100)	//IIS Control
#define IISMOD1  	(0x55000104)	//IIS Mode
#define IISFIC1  	(0x55000108)	//IIS FIFO control
#define IISPSR1  	(0x5500010c)	//IIS clock divider control
#define IISTXD1  	(0x55000110)	//IIS tracsmit data
#define IISRXD1  	(0x55000114)	//IIS recelve data


// chpater26 AC97 - junon
#define	rAC_GLBCTRL		(0x5B000000)
#define	rAC_GLBSTAT		(0x5B000004)
#define	rAC_CODEC_CMD	(0x5B000008)
#define	rAC_CODEC_STAT	(0x5B00000C)
#define	rAC_PCMADDR		(0x5B000010) // edited by junon
#define	rAC_MICADDR		(0x5B000014)
#define	rAC_PCMDATA		(0x5B000018)
#define	rAC_MICDATA		(0x5B00001C)

#ifndef		__S3C2450
// chapter27 SD Interface - gom
#define SDICON     (0x5a000000)	//SDI control
#define SDIPRE     (0x5a000004)	//SDI baud rate prescaler
#define SDICARG    (0x5a000008)	//SDI command argument
#define SDICCON    (0x5a00000c)	//SDI command control
#define SDICSTA    (0x5a000010)	//SDI command status
#define SDIRSP0    (0x5a000014)	//SDI response 0
#define SDIRSP1    (0x5a000018)	//SDI response 1
#define SDIRSP2    (0x5a00001c)	//SDI response 2
#define SDIRSP3    (0x5a000020)	//SDI response 3
#define SDIDTIMER  (0x5a000024)	//SDI data/busy timer
#define SDIBSIZE   (0x5a000028)	//SDI block size
#define SDIDCON    (0x5a00002c)	//SDI data control
#define SDIDCNT    (0x5a000030)	//SDI data remain counter
#define SDIDSTA    (0x5a000034)	//SDI data status
#define SDIFSTA    (0x5a000038)	//SDI FIFO status
#define SDIIMSK    (0x5a00003c)	//SDI interrupt mask. edited for 2442A

#ifdef __BIG_ENDIAN  /* edited for 2442A */
#define SDIDAT		(0x5a00004c)	//SDI data

#else  // Little Endian
#define SDIDAT		(0x5a000040)	//SDI data 
#endif

#endif

// chapter28 HS_MMC Interface - gom
#define HM1_SYSAD      	(0x4A800000)	//SDI control register
#define HM1_BLKSIZE    	(0x4A800004)	//Host buffer boundary and transfer block size register
#define HM1_BLKCNT	    (0x4A800006)	//Block count for current transfer
#define HM1_ARGUMENT   	(0x4A800008)	//Command Argument
#define HM1_TRNMOD	    (0x4A80000C)	//Transfer Mode setting register
#define HM1_CMDREG	    (0x4A80000E)	//Command register
#define HM1_RSPREG0    	(0x4A800010)	//Response 0
#define HM1_RSPREG1    	(0x4A800014)	//Response 1
#define HM1_RSPREG2    	(0x4A800018)	//Response 2
#define HM1_RSPREG3    	(0x4A80001C)	//Response 3
#define HM1_BDATA      	(0x4A800020)	//Buffer Data register
#define HM1_PRNSTS     	(0x4A800024)	//Present state
#define HM1_HOSTCTL    	(0x4A800028)	//Host control
#define HM1_PWRCON     	(0x4A800029)	//Power control
#define HM1_BLKGAP     	(0x4A80002A)	//Block Gap control
#define HM1_WAKCON     	(0x4A80002B)	//Wakeup control
#define HM1_CLKCON     	(0x4A80002C)	//Clock control
#define HM1_TIMEOUTCON  (0x4A80002E)	//Time out control
#define HM1_SWRST      	(0x4A80002F)	//Software reset
#define HM1_NORINTSTS  	(0x4A800030)	//Normal interrupt status
#define HM1_ERRINTSTS  	(0x4A800032)	//Error interrupt status
#define HM1_NORINTSTSEN (0x4A800034)	//Normal interrupt status enable
#define HM1_ERRINTSTSEN (0x4A800036)	//Error interrupt status enable
#define HM1_NORINTSIGEN (0x4A800038)	//Normal interrupt signal enable
#define HM1_ERRINTSIGEN (0x4A80003A)	//Error interrupt signal enable
#define HM1_ACMD12ERRSTS (0x4A80003C)	//Auto CMD12 Error Status
#define HM1_CAPAREG  	(0x4A800040)	//Capability
#define HM1_MAXCURR  	(0x4A800048)	//Maximum current Capability
#define HM1_CONTROL2  	(0x4A800080)	//Control 2
#define HM1_CONTROL3  	(0x4A800084)	//Control 3
#define HM1_HCVER  		(0x4A8000FE)	//Host controller version

#define HM1_DEBUG  		(0x4A800088)
#define HM1_CONTROL4  	(0x4A80008C)
#define HM1_FEAER  		(0x4A800050)
#define HM1_FEERR  		(0x4A800052)
#define HM1_ADMAERR  	(0x4A800054)
#define HM1_ADMSYSADDR  	(0x4A800058)

#define HM0_SYSAD      	(0x4AC00000)		//SDI control register
#define HM0_BLKSIZE    	(0x4AC00004)	//Host buffer boundary and transfer block size register
#define HM0_BLKCNT	    (0x4AC00006)		//Block count for current transfer
#define HM0_ARGUMENT   	(0x4AC00008)		//Command Argument
#define HM0_TRNMOD	    (0x4AC0000C)		//Transfer Mode setting register
#define HM0_CMDREG	    (0x4AC0000E)		//Command register
#define HM0_RSPREG0    	(0x4AC00010)		//Response 0
#define HM0_RSPREG1    	(0x4AC00014)		//Response 1
#define HM0_RSPREG2    	(0x4AC00018)	//Response 2
#define HM0_RSPREG3    	(0x4AC0001C)	//Response 3
#define HM0_BDATA      	(0x4AC00020)	//Buffer Data register
#define HM0_PRNSTS     	(0x4AC00024)	//Present state
#define HM0_HOSTCTL    	(0x4AC00028)	//Host control
#define HM0_PWRCON     	(0x4AC00029)	//Power control
#define HM0_BLKGAP     	(0x4AC0002A)	//Block Gap control
#define HM0_WAKCON     	(0x4AC0002B)	//Wakeup control
#define HM0_CLKCON     	(0x4AC0002C)	//Clock control
#define HM0_TIMEOUTCON  (0x4AC0002E)	//Time out control
#define HM0_SWRST      	(0x4AC0002F)	//Software reset
#define HM0_NORINTSTS  	(0x4AC00030)	//Normal interrupt status
#define HM0_ERRINTSTS  	(0x4AC00032)	//Error interrupt status
#define HM0_NORINTSTSEN (0x4AC00034)	//Normal interrupt status enable
#define HM0_ERRINTSTSEN (0x4AC00036)	//Error interrupt status enable
#define HM0_NORINTSIGEN (0x4AC00038)	//Normal interrupt signal enable
#define HM0_ERRINTSIGEN (0x4AC0003A)	//Error interrupt signal enable
#define HM0_ACMD12ERRSTS (0x4AC0003C)	//Auto CMD12 Error Status
#define HM0_CAPAREG  	(0x4AC00040)	//Capability
#define HM0_MAXCURR  	(0x4AC00048)	//Maximum current Capability
#define HM0_CONTROL2  	(0x4AC00080)	//Control 2
#define HM0_CONTROL3  	(0x4AC00084)	//Control 3
#define HM0_HCVER  		(0x4AC000FE)	//Host controller version

#define HM0_DEBUG  		(0x4AC00088)
#define HM0_CONTROL4  	(0x4AC0008C)
#define HM0_FEAER  		(0x4AC00050)
#define HM0_FEERR  		(0x4AC00052)
#define HM0_ADMAERR  	(0x4AC00054)
#define HM0_ADMSYSADDR  	(0x4AC00058)

// chapter28 PCM - dongjin
#define PCM_CTL0 		(0x5c000000)	//PCM0 Main Control
#define PCM_CLKCTL0 	(0x5c000004)	//PCM0 Clock and Shift control
#define PCM_TXFIFO0 	(0x5c000008)	//PCM0 TxFIFO write port
#define PCM_RXFIFO0 	(0x5c00000C)	//PCM0 RxFIFO read port
#define PCM_IRQ_CTL0 	(0x5c000010)	//PCM0 Interrupt Control
#define PCM_IRQ_STAT0 	(0x5c000014)	//PCM0 Interrupt Status
#define PCM_FIFO_STAT0 (0x5c000018)	//PCM0 Tx Default Value
#define PCM_CLRINT0	(0x5c000020)	//PCM0 Interrupt Clear

#define PCM_CTL1 		(0x5c000100)	//PCM1 Main Control
#define PCM_CLKCTL1 	(0x5c000104)	//PCM1 Clock and Shift control
#define PCM_TXFIFO1 	(0x5c000108)	//PCM1 TxFIFO write port
#define PCM_RXFIFO1 	(0x5c00010C)	//PCM1 RxFIFO read port
#define PCM_IRQ_CTL1 	(0x5c000110)	//PCM1 Interrupt Control
#define PCM_IRQ_STAT1 	(0x5c000114)	//PCM1 Interrupt Status
#define PCM_FIFO_STAT1 (0x5c000118)	//PCM1 Tx Default Value
#define PCM_CLRINT1	(0x5c000120)	//PCM1 Interrupt Clear

// chapter29 HS_MMC Interface - gom
#define HM_SYSAD      	(0x4A800000)	//SDI control register
#define HM_BLKSIZE    	(0x4A800004)	//Host buffer boundary and transfer block size register
#define HM_BLKCNT	    (0x4A800006)	//Block count for current transfer
#define HM_ARGUMENT   	(0x4A800008)	//Command Argument
#define HM_TRNMOD	    (0x4A80000C)	//Transfer Mode setting register
#define HM_CMDREG	    (0x4A80000E)	//Command register
#define HM_RSPREG0    	(0x4A800010)	//Response 0
#define HM_RSPREG1    	(0x4A800014)	//Response 1
#define HM_RSPREG2    	(0x4A800018)	//Response 2
#define HM_RSPREG3    	(0x4A80001C)	//Response 3
#define HM_BDATA      	(0x4A800020)	//Buffer Data register
#define HM_PRNSTS     	(0x4A800024)	//Present state
#define HM_HOSTCTL    	(0x4A800028)	//Host control
#define HM_PWRCON     	(0x4A800029)	//Power control
#define HM_BLKGAP     	(0x4A80002A)	//Block Gap control
#define HM_WAKCON     	(0x4A80002B)	//Wakeup control
#define HM_CLKCON     	(0x4A80002C)	//Clock control
#define HM_TIMEOUTCON  (0x4A80002E)	//Time out control
#define HM_SWRST      	(0x4A80002F)	//Software reset
#define HM_NORINTSTS  	(0x4A800030)	//Normal interrupt status
#define HM_ERRINTSTS  	(0x4A800032)	//Error interrupt status
#define HM_NORINTSTSEN (0x4A800034)	//Normal interrupt status enable
#define HM_ERRINTSTSEN (0x4A800036)	//Error interrupt status enable
#define HM_NORINTSIGEN (0x4A800038)	//Normal interrupt signal enable
#define HM_ERRINTSIGEN (0x4A80003A)	//Error interrupt signal enable
#define HM_ACMD12ERRSTS (0x4A80003C)	//Auto CMD12 Error Status
#define HM_CAPAREG  	(0x4A800040)	//Capability
#define HM_MAXCURR  	(0x4A800048)	//Maximum current Capability
#define HM_CONTROL2  	(0x4A800080)	//Control 2
#define HM_CONTROL3  	(0x4A800084)	//Control 3
#define HM_HCVER  		(0x4A8000FE)	//Host controller version


// PENDING BIT
#define BIT_EINT0		(0x1)
#define BIT_EINT1		(0x1<<1)
#define BIT_EINT2		(0x1<<2)
#define BIT_EINT3		(0x1<<3)
#define BIT_EINT4_7		(0x1<<4)
#define BIT_EINT8_23	(0x1<<5)
#define BIT_CAM			(0x1<<6)		
#define BIT_BAT_FLT		(0x1<<7)
#define BIT_TICK			(0x1<<8)
#define BIT_WDT_AC97	(0x1<<9)	
#define BIT_TIMER0		(0x1<<10)
#define BIT_TIMER1		(0x1<<11)
#define BIT_TIMER2		(0x1<<12)
#define BIT_TIMER3		(0x1<<13)
#define BIT_TIMER4		(0x1<<14)
#define BIT_UART2		(0x1<<15)
#define BIT_LCD			(0x1<<16)
#define BIT_DMA			(0x1<<17)		//changed at 2443
#define BIT_UART3		(0x1<<18)		//changed at 2443
#define BIT_CFCON		(0x1<<19)		//changed at 2443
#define BIT_SDI1			(0x1<<20)		//changed at 2443
#define BIT_SDI0			(0x1<<21)		//changed at 2443
#define BIT_SPI0			(0x1<<22)		//changed at 2443
#define BIT_UART1		(0x1<<23)
#define BIT_NFCON		(0x1<<24)		
#define BIT_USBD		(0x1<<25)
#define BIT_USBH		(0x1<<26)
#define BIT_IIC			(0x1<<27)
#define BIT_UART0		(0x1<<28)
#define BIT_SPI1			(0x1<<29)		//changed at 2443
#define BIT_RTC			(0x1<<30)
#define BIT_ADC			(0x1<<31)
#define BIT_ALLMSK		(0xffffffff)

// PENDING BIT 2
#define BIT_2D			(0x1)
#define BIT_IIC1		(0x1<<1)
#define BIT_ReservedIRQ0	(0x1<<2)
#define BIT_ReservedIRQ1	(0x1<<3)
#define BIT_PCM0		(0x1<<4)
#define BIT_PCM1		(0x1<<5)
#define BIT_I2S0		(0x1<<6)		
#define BIT_I2S1		(0x1<<7)
#define BIT_ALLMSK2	(0xff)

// SUB PENDING BIT
#define BIT_SUB_ALLMSK	(0x1fffffff)		//Changed from 0x7fff to 0x1fffffff at 2443
#define BIT_SUB_AC97	(0x1<<28)		//changed at 2443
#define BIT_SUB_WDT		(0x1<<27)		//changed at 2443
#define BIT_SUB_ERR3	(0x1<<26)		//changed at 2443
#define BIT_SUB_TXD3	(0x1<<25)		//changed at 2443
#define BIT_SUB_RXD3	(0x1<<24)		//changed at 2443
#define BIT_SUB_DMA7	(0x1<<30)		//changed at 2443
#define BIT_SUB_DMA6	(0x1<<29)		//changed at 2443
#define BIT_SUB_DMA5	(0x1<<23)		//changed at 2443
#define BIT_SUB_DMA4	(0x1<<22)		//changed at 2443
#define BIT_SUB_DMA3	(0x1<<21)		//changed at 2443
#define BIT_SUB_DMA2	(0x1<<20)		//changed at 2443
#define BIT_SUB_DMA1	(0x1<<19)		//changed at 2443
#define BIT_SUB_DMA0	(0x1<<18)		//changed at 2443
#define BIT_SUB_LCD4	(0x1<<17)		//changed at 2443
#define BIT_SUB_LCD3	(0x1<<16)		//changed at 2443
#define BIT_SUB_LCD2	(0x1<<15)		//changed at 2443
#define BIT_SUB_LCD1	(0x1<<14)		//changed at 2443
#define BIT_SUB_CAM_P	(0x1<<12)		
#define BIT_SUB_CAM_C   (0x1<<11)       
#define BIT_SUB_ADC		(0x1<<10)
#define BIT_SUB_TC		(0x1<<9)
#define BIT_SUB_ERR2	(0x1<<8)
#define BIT_SUB_TXD2	(0x1<<7)
#define BIT_SUB_RXD2	(0x1<<6)
#define BIT_SUB_ERR1	(0x1<<5)
#define BIT_SUB_TXD1	(0x1<<4)
#define BIT_SUB_RXD1	(0x1<<3)
#define BIT_SUB_ERR0	(0x1<<2)
#define BIT_SUB_TXD0	(0x1<<1)
#define BIT_SUB_RXD0	(0x1<<0)


#define ClearPending(bit) {\
               rSRCPND = bit;\
               rINTPND = bit;\
               rINTPND;\
                }             
#define ClearPending2(bit) {\
               rSRCPND2 = bit;\
               rINTPND2 = bit;\
               rINTPND2;\
                }    
// Wait until rINTPND is changed for the case that the ISR is very short.       
// The effect of reading "rINTPND;" : Waiting until rINTPND is changed.
// When you access any address, write buffer must be cleared if you want to read this address.
// Otherwise, twice interrupt request could be occured per one interrupt.
// in the case that the ISR is very short.

#ifdef __cplusplus
}
#endif

#endif 
