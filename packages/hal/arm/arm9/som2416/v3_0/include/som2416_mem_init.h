//ddr2 mem settings
//

#define BANKCFGVAL   		((RASBW0<<17)+(RASBW1<<14)+(CASBW0<<11)+(CASBW1<<8)+(ADDRCFG0<<6)+(ADDRCFG1<<4)+(MEMCFG<<1)+(BW<<0))
#define BANKCON1VAL  		((DQSDelay<<28)+(1<<26)+(BStop<<7)+(WBUF<<6)+(AP<<5)+(PWRDN<<4))
#define BANKCON2VAL  		((tRAS<<20)+(tARFC<<16)+(CL<<4)+(tRCD<<2)+(tRP<<0))

#define Startup_EMdiv		 	32			// EPLL -> 96Mhz
#define Startup_EPdiv		   	1
#define Startup_ESdiv		 	2	

//---------------------------------------
// BANKCFG register  : DDR2 SDRAM configure
//---------------------------------------
#define RASBW0						2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define RASBW1						2			//	RAS addr 00=11bit,01-12bit,10=13bit, 11=14bit
#define CASBW0						2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define CASBW1						2			//	CAS addr 00=8bit,01-9bit,10=10bit, 11=11bit
#define ADDRCFG0					1			// 	addre configure
												//   00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define ADDRCFG1					1			// 	addre configure
												//   00={BA,RAS,CAS}, 01={RAS,BA,CAS}
#define MEMCFG						1			// 	Ext.Mem 000=SDR,010=MSDR,100=DDRz,110=MDDR,001=DDR2
#define BW						1			// 	Bus width 00=32bit,01=16bit


//---------------------------------------
// BANKCON1 register : DDR2 SDRAM timing control
//---------------------------------------
#define PADLOAD						1
#define BStop						0			//	read burst stop control
#define WBUF						1			//	write buffer control
#define AP							0			//	auto precharge control
#define PWRDN						0			//	power down mode
#define DQSDelay					4			//	DQS delay

//---------------------------------------
// BANKCON2 register : DDR2 SDRAM timing control
//---------------------------------------
#define tRAS						5			//	Row active time
#define tARFC						13			//	Row cycle time
#define CL						3			//	CAS latency control
#define tRCD						1			//	RAS to CAS delay
#define tRP						1			// 	Row pre-charge time


//---------------------------------------
// BANKCON3 register : DDR2 SDRAM MRS/EMRS register
//---------------------------------------
#define BA_EMRS1					1			//	BA : EMRS
#define DLL_DIS						1
#define DLL_EN						0
#define nDQS_DIS					1
#define RDQS_DIS					0
#define OCD_MODE_EXIT					0
#define OCD_MODE_DEFAULT				7
#define BA_EMRS2					2			//	BA : EMRS
#define BA_EMRS3					3			//	BA : EMRS
#define DS						0			//	Driver strength
#define PASR						0			//	PASR
#define BA_MRS						0			//	BA : MRS
#define TM						0			// 	Test Mode - mode register set
#define CL_MRS						3			// 	CAS Latency
#define DLL_RESET_HIGH					1
#define DLL_RESET_LOW					0

//---------------------------------------
// REFRESH register : DDR2 SDRAM refresh register
//---------------------------------------
#define REFCYC						1037			// 	refresh cycle
//---------------------------------------------------------------------------

	.macro SOM2416_MEM_INIT
InitMEM:
				//Set GPK port when using x32 bus width.
				ldr		r0,=GPKCON
				ldr		r1,=0xaaaaaaaa	// set Sdata[31:16]
				str		r1, [r0]
				
				//Set DDR2 Memory parameter control registers
				ldr		r0,=BANKCFG
				ldr		r1,=BANKCFGVAL 	// set Sdata[31:16]
				str		r1, [r0]

				ldr		r0,=BANKCON1
				ldr		r1,=BANKCON1VAL  	// set Sdata[31:16]
				str		r1, [r0]


				ldr		r0,=BANKCON2
				ldr		r1,=BANKCON2VAL   	// set Sdata[31:16]
				str		r1, [r0]
				

				ldr		r2,=BANKCON1			//	4nd	:	Issue a PALL command
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x1<<0)			
				str		r1,[r2]	

				ldr		r2,=BANKCON3			//	5th	:	Issue a EMRS2 command
				ldr		r3,=0xffff0000
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,#(BA_EMRS2<<30)
				str		r1,[r2]	

				ldr		r2,=BANKCON1
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x3<<0)			
				str		r1,[r2]

				ldr		r2,=BANKCON3			//	6th	:	Issue a EMRS3 command
				ldr		r3,=0xffff0000
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,#(BA_EMRS3<<30)
				str		r1,[r2]

				ldr		r2,=BANKCON1
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x3<<0)			
				str		r1,[r2]

				ldr		r2,=BANKCON3			//	7th	:	Issue a EMRS1 command
				ldr		r3,=0xffff0000
				ldr		r4,=((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16)) 
				                      // (0x1<<30)|(0x0<<27)|(0x1<<26)|(0x0<<23)|(0x0<<16)
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,r4
				str		r1,[r2]

				ldr		r2,=BANKCON1
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x3<<0)			
				str		r1,[r2]

				ldr		r2,=BANKCON3			//	8th	:	Issue a MRS command
				ldr		r3,=0xffff
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,#((BA_MRS<<14)+(DLL_RESET_HIGH<<8)+(TM<<7)+(CL_MRS<<4))
				str		r1,[r2]
				
				ldr		r2,=BANKCON1				
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x2<<0)			
				str		r1,[r2]

				ldr		r2,=BANKCON1			//	9nd	:	Issue a PALL command
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x1<<0)			
				str		r1,[r2]

				ldr		r4,=REFRESH				//	10th : wait 2 auto - clk
				ldr		r0,=0x20
				str		r0,[r4]					
				
				ldr		r2,=BANKCON3			//	11th	:	Issue a MRS command
				ldr		r3,=0xffff
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,#((BA_MRS<<14)+(DLL_RESET_LOW<<8)+(TM<<7)+(CL_MRS<<4))
				str		r1,[r2]
				
				ldr		r2,=BANKCON1				
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x2<<0)			
				str		r1,[r2]

				mov	r0, #0x100					//	Wait 200 clock
2:				subs	r0, r0,#1//
				bne	2b
				
				ldr		r2,=BANKCON3			//	12th	:	Issue a EMRS1 command For OCD Mode Set to default
				ldr		r3,=0xffff0000
				ldr		r4,=((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_DEFAULT<<23)+(DLL_EN<<16))
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,r4
				str		r1,[r2]

				ldr		r2,=BANKCON1
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x3<<0)			
				str		r1,[r2]

				ldr		r2,=BANKCON3
				ldr		r3,=0xffff0000
				ldr		r4,=((BA_EMRS1<<30)+(RDQS_DIS<<27)+(nDQS_DIS<<26)+(OCD_MODE_EXIT<<23)+(DLL_EN<<16))
				ldr		r1,[r2]
				bic		r1,r1,r3
				orr		r1,r1,r4
				str		r1,[r2]

				ldr		r2,=BANKCON1
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				orr		r1,r1,#(0x3<<0)			
				str		r1,[r2]
				
				ldr		r4,=REFRESH			//	13fh : refresh  normal
				ldr		r0,=REFCYC
				str		r0,[r4]					

				ldr		r2,=BANKCON1		//	14th	:	Issue a Normal mode
				ldr		r1,[r2]
				bic		r1,r1,#(0x3<<0)
				str		r1,[r2]
	.endm
