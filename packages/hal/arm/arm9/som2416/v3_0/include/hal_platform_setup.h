#ifndef CYGONCE_HAL_PLATFORM_SETUP_H
#define CYGONCE_HAL_PLATFORM_SETUP_H
//=============================================================================
//
//      hal_platform_setup.h
//
//      Platform specific support for HAL (assembly code)
//
//=============================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//=============================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    michael anburaj <michaelanburaj@hotmail.com>
// Contributors: michael anburaj <michaelanburaj@hotmail.com>
// Date:         2003-08-01
// Purpose:      ARM9/SOM2416 platform specific support routines
// Description: 
// Usage:        #include <cyg/hal/hal_platform_setup.h>
//     Only used by "vectors.S"         
//
//####DESCRIPTIONEND####
//
//=============================================================================

#include <pkgconf/system.h>           // System-wide configuration info
#include CYGBLD_HAL_VARIANT_H         // Variant specific configuration
#include CYGBLD_HAL_PLATFORM_H        // Platform specific configuration
#include CYGHWR_MEMORY_LAYOUT_H
#include <cyg/hal/hal_mmu.h>          // MMU definitions
#include <cyg/hal/s3c2416.h>         // Platform specific hardware definitions
#include <cyg/hal/memcfg.h>           // Platform specific memory configuration
#include <cyg/hal/som2416_mem_init.h> //njs add som2416 ddr2 mem init 

// MPLL=(m*Fin)/(p*2^s)
#if (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 200000000)
#define M_MDIV      200                  // Fin=12.0MHz Fout=200.0MHz
#define M_PDIV      3
#define M_SDIV      2
#elif (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 243000000)
#define M_MDIV      81 
#define M_PDIV      2
#define M_SDIV      1
#elif (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 300000000)
#define M_MDIV      200
#define M_PDIV      2
#define M_SDIV      2
#elif (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 350000000)
#define M_MDIV      350                  
#define M_PDIV      3
#define M_SDIV      2
#elif (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 400000000)
#define M_MDIV      200                  
#define M_PDIV      3
#define M_SDIV      1
#elif (CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK == 486000000)
#define M_MDIV      162                  
#define M_PDIV      2
#define M_SDIV      1
#else
#error CYGNUM_HAL_ARM_SOM2416_CPU_CLOCK not set to the right value
#endif


#if defined(CYG_HAL_STARTUP_ROM) || defined(CYG_HAL_STARTUP_ROMRAM)
#define PLATFORM_SETUP1 _platform_setup1
#define CYGHWR_HAL_ARM_HAS_MMU
//#if defined(CYG_HAL_STARTUP_ROM)  //njs add this if prefix, for my app reset no from rom.
#define CYGSEM_HAL_ROM_RESET_USES_JUMP
//#endif
// We need this here - can't rely on a translation table until MMU has
// been initialized
//
#define CYGHWR_LED_MACRO RAW_LED_MACRO

        .macro RAW_LED_MACRO x
        ldr     r0,=GPCDAT  //GPC5, LED
        ldr     r1,[r0]
		mov		r2,#(\x)
	    and		r2,r2,#(0x1<<5)
        bic     r1,r1,#(0x1<<5)
        orr     r1,r1,r2
        str     r1, [r0]
        .endm


        // Configure GPC[5] as Output & pull-up turned off
        .macro RAW_LED_PORT_INIT_MACRO
        ldr     r0,=GPCUDP
        ldr     r1,[r0]
        orr     r1,r1,#(1<<10) //pull down enable
        str     r1,[r0]

        RAW_LED_MACRO 0

        ldr     r0,=GPCCON
        ldr     r1,[r0]
        orr     r1,r1,#(1<<10)
        str     r1,[r0]
        .endm

// This macro represents the initial startup code for the platform        
        .macro  _platform_setup1
#ifndef CYG_HAL_STARTUP_RAM
        ldr    r0,=WTCON            // watch dog disable 
        ldr    r1,=0x0         
        str    r1,[r0]
#endif
        RAW_LED_PORT_INIT_MACRO

#ifndef CYG_HAL_STARTUP_RAM
        ldr    r0,=INTMSK
        ldr    r1,=0xffffffff       // all interrupt disable
        str    r1,[r0]

        ldr    r0,=INTSUBMSK
        ldr    r1,=0xffffffff            // all sub interrupt disable
        str    r1,[r0]

		ldr     r0, = INTMOD
		mov r1, #0x0				//; set all interrupt as IRQ (not FIQ)
		str     r1, [r0]

        RAW_LED_MACRO 1

        // Disable and clear caches
        mrc  p15,0,r0,c1,c0,0
        bic  r0,r0,#0x1000              // disable ICache
        bic  r0,r0,#0x000f              // disable DCache, write buffer,
                                        // MMU and alignment faults
        mcr  p15,0,r0,c1,c0,0
        nop
        nop
        mov  r0,#0
        mcr  p15,0,r0,c7,c6,0           // clear data cache
#if 0
        mrc  p15,0,r0,c15,c1,0          // disable streaming
        orr  r0,r0,#0x80
        mcr  p15,0,r0,c15,c1,0
#endif

//				; Clock configuration

				ldr		r0, =CLKDIV0			//; Set Clock Divider
				ldr		r1, [r0]
				bic		r1, r1, #0x37			//; clear HCLKDIV, PREDIV, PCLKDIV
				bic		r1, r1, #(0xf<<9)		//; clear ARMCLKDIV
				ldr		r2, =((Startup_ARMCLKdiv<<9)+(Startup_PREdiv<<4)+(Startup_PCLKdiv<<2)+(Startup_HCLKdiv))
				orr		r1, r1, r2
				str		r1, [r0]				
				
				ldr		r0, =LOCKCON0		//; Set lock time of MPLL. added by junon
				mov		r1, #0xe10			//; Fin = 12MHz -0x800, 16.9844MHz -0xA00
				str		r1, [r0]

				ldr		r0,=LOCKCON1		//;	Set lock time of EPLL. added by junon
				mov		r1,#0x800			//;	Fin = 12MHz - 0x800, 16.9844MHz - 0xA00
				str		r1,[r0]	

				ldr		r0, =MPLLCON			//; Set MPLL
				ldr		r1,=((0<<24)+(M_MDIV<<14)+(M_PDIV<<5)+(M_SDIV))
				str		r1, [r0]

			  	ldr		r0,=EPLLCON			//;	Set EPLL
				ldr		r1,=((0<<24)+(Startup_EMdiv<<16)+(Startup_EPdiv<<8)+(Startup_ESdiv))
				str		r1,[r0]				//; EPLL=(MDIV*Fin)/(PDIV*2SDIV)

				ldr		r0, =CLKSRC			//; Select MPLL clock out for SYSCLK
				ldr		r1, [r0]
				orr		r1, r1, #0x50
				str		r1, [r0]

        // MMU_SetAsyncBusMode  //Must select, since we're setting HDIVN=1
#define R1_iA   (1<<31)
#define R1_nF   (1<<30)
        mrc     p15,0,r0,c1,c0,0
        orr     r0,r0,#(R1_nF|R1_iA)
        mcr     p15,0,r0,c1,c0,0
		
//		SOM2416_MEM_INIT
2:
//        RAW_LED_MACRO 0

#endif /* !CYG_HAL_STARTUP_RAM */

        // Set up a stack [for calling C code]
        ldr     r1,=__startup_stack
        ldr     r2,=SOM2416_SDRAM_PHYS_BASE
        orr     sp,r1,r2

        // Create MMU tables
        bl      hal_mmu_init

        // Enable MMU
        ldr     r2,=10f
//#ifdef CYG_HAL_STARTUP_ROMRAM
#if 0
        ldr     r1,=__exception_handlers
        ldr r9,=0x80000000
        sub     r1,r2,r1		//r1=10f offset from exception_handlers
        add     r2,r9,r1        // r9 has ROM offset; r2= 8000,0000,+(10f-excetpion_handlers). 
#endif        
        ldr        r1,=MMU_Control_Init|MMU_Control_M
        mcr        MMU_CP,0,r1,MMU_Control,c0
        mov        pc,r2    /* Change address spaces */
        nop
        nop
        nop
10:
        
//#ifdef CYG_HAL_STARTUP_ROMRAM
#if 0
        mov     r0,r9                     // Relocate FLASH/ROM to RAM
        ldr     r1,=__exception_handlers  // ram base & length
        ldr     r2,=__rom_data_end			//memcpy(0x8000/0000,_exceptionhandlers,_romd_data_end-exception handler)??
										//after mmu enable; __exceptionHandler was sram area; 0x8000 was the old rom area.
20:     ldr     r3,[r0],#4
        str     r3,[r1],#4
        cmp     r1,r2
        bne     20b
        ldr     r0,=30f
        mov     pc,r0
        nop
        nop
        nop
        nop
30:             
#endif
//        RAW_LED_MACRO 0
        .endm
        
#else // defined(CYG_HAL_STARTUP_ROM) || defined(CYG_HAL_STARTUP_ROMRAM)
#define PLATFORM_SETUP1
#endif

//-----------------------------------------------------------------------------
// end of hal_platform_setup.h
#endif // CYGONCE_HAL_PLATFORM_SETUP_H
