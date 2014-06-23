//==========================================================================
//
//      som2416_misc.c
//
//      HAL misc board support code for ARM9/SOM2416
//
//==========================================================================
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
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):    michael anburaj <michaelanburaj@hotmail.com>
// Contributors: michael anburaj <michaelanburaj@hotmail.com>
// Date:         2003-08-01
// Purpose:      HAL board support
// Description:  Implementations of HAL board interfaces
//
//####DESCRIPTIONEND####
//
//==========================================================================

#include <pkgconf/hal.h>
#include <pkgconf/system.h>
#include CYGBLD_HAL_PLATFORM_H

#include <cyg/infra/cyg_type.h>         // base types
#include <cyg/infra/cyg_trac.h>         // tracing macros
#include <cyg/infra/cyg_ass.h>          // assertion macros

#include <cyg/hal/hal_io.h>             // IO macros
#include <cyg/hal/hal_arch.h>           // Register state info
#include <cyg/hal/hal_diag.h>
#include <cyg/hal/hal_intr.h>           // Interrupt names
#include <cyg/hal/hal_cache.h>
#include <cyg/hal/s3c2416.h>           // Platform specifics

#include <cyg/infra/diag.h>             // diag_printf

#include <string.h>                     // memset

// -------------------------------------------------------------------------
// MMU initialization:
// 
// These structures are laid down in memory to define the translation
// table.
// 

// ARM Translation Table Base Bit Masks
#define ARM_TRANSLATION_TABLE_MASK               0xFFFFC000

// ARM Domain Access Control Bit Masks
#define ARM_ACCESS_TYPE_NO_ACCESS(domain_num)    (0x0 << (domain_num)*2)
#define ARM_ACCESS_TYPE_CLIENT(domain_num)       (0x1 << (domain_num)*2)
#define ARM_ACCESS_TYPE_MANAGER(domain_num)      (0x3 << (domain_num)*2)

struct ARM_MMU_FIRST_LEVEL_FAULT {
    int id : 2;
    int sbz : 30;
};
#define ARM_MMU_FIRST_LEVEL_FAULT_ID 0x0

struct ARM_MMU_FIRST_LEVEL_PAGE_TABLE {
    int id : 2;
    int imp : 2;
    int domain : 4;
    int sbz : 1;
    int base_address : 23;
};
#define ARM_MMU_FIRST_LEVEL_PAGE_TABLE_ID 0x1

struct ARM_MMU_FIRST_LEVEL_SECTION {
    int id : 2;
    int b : 1;
    int c : 1;
    int imp : 1;
    int domain : 4;
    int sbz0 : 1;
    int ap : 2;
    int sbz1 : 8;
    int base_address : 12;
};
#define ARM_MMU_FIRST_LEVEL_SECTION_ID 0x2

struct ARM_MMU_FIRST_LEVEL_RESERVED {
    int id : 2;
    int sbz : 30;
};
#define ARM_MMU_FIRST_LEVEL_RESERVED_ID 0x3

#define ARM_MMU_FIRST_LEVEL_DESCRIPTOR_ADDRESS(ttb_base, table_index) \
   (unsigned long *)((unsigned long)(ttb_base) + ((table_index) << 2))

#define ARM_FIRST_LEVEL_PAGE_TABLE_SIZE 0x4000

#define ARM_MMU_SECTION(ttb_base, actual_base, virtual_base,              \
                        cacheable, bufferable, perm)                      \
    CYG_MACRO_START                                                       \
        register union ARM_MMU_FIRST_LEVEL_DESCRIPTOR desc;               \
                                                                          \
        desc.word = 0;                                                    \
        desc.section.id = ARM_MMU_FIRST_LEVEL_SECTION_ID;                 \
        desc.section.imp = 1;                                             \
        desc.section.domain = 0;                                          \
        desc.section.c = (cacheable);                                     \
        desc.section.b = (bufferable);                                    \
        desc.section.ap = (perm);                                         \
        desc.section.base_address = (actual_base);                        \
        *ARM_MMU_FIRST_LEVEL_DESCRIPTOR_ADDRESS(ttb_base, (virtual_base)) \
                            = desc.word;                                  \
    CYG_MACRO_END

#define X_ARM_MMU_SECTION(abase,vbase,size,cache,buff,access)      \
    { int i; int j = abase; int k = vbase;                         \
      for (i = size; i > 0 ; i--,j++,k++)                          \
      {                                                            \
        ARM_MMU_SECTION(ttb_base, j, k, cache, buff, access);      \
      }                                                            \
    }

union ARM_MMU_FIRST_LEVEL_DESCRIPTOR {
    unsigned long word;
    struct ARM_MMU_FIRST_LEVEL_FAULT fault;
    struct ARM_MMU_FIRST_LEVEL_PAGE_TABLE page_table;
    struct ARM_MMU_FIRST_LEVEL_SECTION section;
    struct ARM_MMU_FIRST_LEVEL_RESERVED reserved;
};

#define ARM_UNCACHEABLE                         0
#define ARM_CACHEABLE                           1
#define ARM_UNBUFFERABLE                        0
#define ARM_BUFFERABLE                          1

#define ARM_ACCESS_PERM_NONE_NONE               0
#define ARM_ACCESS_PERM_RO_NONE                 0
#define ARM_ACCESS_PERM_RO_RO                   0
#define ARM_ACCESS_PERM_RW_NONE                 1
#define ARM_ACCESS_PERM_RW_RO                   2
#define ARM_ACCESS_PERM_RW_RW                   3

//njs add-------
static unsigned int uMPLL;
static unsigned int uARMCLK, uHCLK, uPCLK;
static unsigned int uARMCLKdiv, uPREdiv, uHCLKdiv, uPCLKdiv;

void
hal_mmu_init(void)
{
    unsigned long ttb_base = SOM2416_SDRAM_PHYS_BASE + 0x4000;
    unsigned long i;

    // Set the TTB register
    asm volatile ("mcr  p15,0,%0,c2,c0,0" : : "r"(ttb_base) /*:*/);

    // Set the Domain Access Control Register
    i = ARM_ACCESS_TYPE_MANAGER(0)    | 
        ARM_ACCESS_TYPE_NO_ACCESS(1)  |
        ARM_ACCESS_TYPE_NO_ACCESS(2)  |
        ARM_ACCESS_TYPE_NO_ACCESS(3)  |
        ARM_ACCESS_TYPE_NO_ACCESS(4)  |
        ARM_ACCESS_TYPE_NO_ACCESS(5)  |
        ARM_ACCESS_TYPE_NO_ACCESS(6)  |
        ARM_ACCESS_TYPE_NO_ACCESS(7)  |
        ARM_ACCESS_TYPE_NO_ACCESS(8)  |
        ARM_ACCESS_TYPE_NO_ACCESS(9)  |
        ARM_ACCESS_TYPE_NO_ACCESS(10) |
        ARM_ACCESS_TYPE_NO_ACCESS(11) |
        ARM_ACCESS_TYPE_NO_ACCESS(12) |
        ARM_ACCESS_TYPE_NO_ACCESS(13) |
        ARM_ACCESS_TYPE_NO_ACCESS(14) |
        ARM_ACCESS_TYPE_NO_ACCESS(15);
    asm volatile ("mcr  p15,0,%0,c3,c0,0" : : "r"(i) /*:*/);

    // First clear all TT entries - ie Set them to Faulting
    memset((void *)ttb_base, 0, ARM_FIRST_LEVEL_PAGE_TABLE_SIZE);

    // Memory layout after MMU is turned on
    //
    //   SDRAM_BASE_ADDRESS:     0x00000000,  64M
    //   SRAM_BASE_ADDRESS:      0x40000000,   4K
    //   SFR_BASE_ADDRESS:       0x48000000, 512M
    //   FLASH_BASE_ADDRESS:     0x80000000,   2M

    //               Actual  Virtual  Size   Attributes                                                  Function
    //               Base     Base     MB     cached?          buffered?         access permissions
    //             xxx00000  xxx00000
    X_ARM_MMU_SECTION(0x000,  0x800,    2,  ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW); // Flash
    X_ARM_MMU_SECTION(0x300,  0x000,   64,  ARM_CACHEABLE,   ARM_BUFFERABLE,   ARM_ACCESS_PERM_RW_RW); // SDRAM
//    X_ARM_MMU_SECTION(0x300,  0x000,   64,  ARM_UNCACHEABLE,   ARM_UNBUFFERABLE,   ARM_ACCESS_PERM_RW_RW); // SDRAM
    X_ARM_MMU_SECTION(0x400,  0x400,    1,  ARM_CACHEABLE,   ARM_BUFFERABLE,   ARM_ACCESS_PERM_RW_RW); // SRAM
    X_ARM_MMU_SECTION(0x480,  0x480,  512,  ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW); // SFRs
    X_ARM_MMU_SECTION(0x300,  0x300,   64,  ARM_UNCACHEABLE, ARM_UNBUFFERABLE, ARM_ACCESS_PERM_RW_RW); // Raw SDRAM
}

//----------------------------------------------------------------------------
// Platform specific initialization

// This routine sets the default GPIO condition
static void port_init(void)
{
	//not configure port.
	//every part of the software should configure the I/O port for It's uses.
}
void SystemCLK() // edited by junon 060522, 060624
{
	unsigned int mdiv, pdiv, sdiv;

	mdiv = (rMPLLCON>>14)&0x3ff;
	pdiv = (rMPLLCON>>5)&0x3f;
	sdiv = (rMPLLCON&0x3);

	uMPLL = mdiv*(FIN/pdiv);
	uMPLL >>= sdiv;

	uARMCLKdiv	=	(rCLKDIV0>>9) & 0xf; // [12:9]=ARMDIV -> 1/1 ~ 1/16
	uPREdiv      =   (rCLKDIV0>>4) & 0x3;  // [5:4]=PREDIV	   
	uHCLKdiv		=	 rCLKDIV0 & 0x3; // [0:1]=HCLKDIV		 
	uPCLKdiv		=	(rCLKDIV0>>2) & 1;

	uARMCLK	=	uMPLL / ( ((uARMCLKdiv>>3)+1) * ((uARMCLKdiv&7)+1) ); 
	uHCLK	=	uMPLL / ( ((uPREdiv&3)+1) * ((uHCLKdiv&3)+1) );
	uPCLK	=	uHCLK>>uPCLKdiv;

//	 make 1MHz Timer clock = PCLK / Prescaler(PCLK/2M-1) + 1 / Divider(2)
	// (1M)*val=PCLK/2->val=PCLK/(2M)
	rTCFG0	=(rTCFG0 & (~(0xffff<<8)))	| ((uPCLK/2000000-1)<<8);		//  prescaler of timer2,3,4[8..15]
	
}

void
plf_hardware_init(void)
{
    HAL_WRITE_UINT32(INTMOD, 0x0);                     //All=IRQ mode
    HAL_WRITE_UINT32(INTMSK, BIT_ALLMSK);              //All interrupt is masked.
    HAL_WRITE_UINT32(INTSUBMSK, BIT_SUB_ALLMSK);       //All sub-interrupt is masked.

    port_init();

	SystemCLK();
    // Initialize real-time clock (for delays, etc, even if kernel doesn't use it)
    hal_clock_initialize(CYGNUM_HAL_RTC_PERIOD);
}

// -------------------------------------------------------------------------
// Use Timer4 for system clock
void
hal_clock_initialize(cyg_uint32 period)
{
    cyg_uint32 temp;

    // Configure the MUX to select the 1/2 divider
    HAL_WRITE_UINT32(TCFG1, 0); //500kHz, timer4, input
  /* 
    // Configure the Prescaler1
    HAL_READ_UINT32(TCFG0, temp);
    temp &= ~(0xff<<8);
    temp |= (CYGNUM_HAL_ARM_SMDK2410_TIMER_PRESCALE<<8);
    HAL_WRITE_UINT32(TCFG0, temp);

    // Configure the MUX to select the 1/2 divider
    HAL_READ_UINT32(TCFG1, temp);
    temp &= ~(0xf<<16);
    temp |= (0x0<<16);
    HAL_WRITE_UINT32(TCFG1, temp);
*/ 
    // Set up the Timer4 for period
//    HAL_WRITE_UINT32(TCNTB4, period);
	HAL_WRITE_UINT32(TCNTB4,10101); //100ms

    // Start Timer4
    HAL_READ_UINT32(TCON, temp);
    temp &= ~(0xf << 20);
    HAL_WRITE_UINT32(TCON, (temp|(6<<20)));
    HAL_WRITE_UINT32(TCON, (temp|(5<<20)));

    // Unmask Timer4 interrupt, need not be done here
    //HAL_INTERRUPT_CONFIGURE( CYGNUM_HAL_INTERRUPT_RTC, 1, 1 );
    //HAL_INTERRUPT_UNMASK( CYGNUM_HAL_INTERRUPT_RTC );
}

// This routine is called during a clock interrupt.
void
hal_clock_reset(cyg_uint32 vector, cyg_uint32 period)
{
    // Do nothing
}

// Read the current value of the clock, returning the number of hardware
// "ticks" that have occurred (i.e. how far away the current value is from
// the start)
void
hal_clock_read(cyg_uint32 *pvalue)
{
    cyg_int32 clock_val;

    // Read Timer4's current value
    HAL_READ_UINT32(TCNTO4, clock_val);

    *pvalue = CYGNUM_HAL_RTC_PERIOD - (clock_val & 0xFFFF);   // Note: counter is only 16 bits
                                                              // and decreases
}


// Delay for some number of micro-seconds
void 
hal_delay_us(cyg_int32 usecs)
{
    cyg_uint32 ticks = 0;
    // Divide by 1000000 in two steps to preserve precision.
    cyg_uint32 wait_ticks = (((PCLK/100000)*usecs)/CYGNUM_HAL_ARM_SOM2416_TIMER_PRESCALE/2/10);
    cyg_int32 val, prev, diff;

    // Read Timer4's current value
    HAL_READ_UINT32(TCNTO4, prev);
    prev &= 0xFFFF;

    while (ticks < wait_ticks) {
        while (true) {
            // Read Timer4's current value
            HAL_READ_UINT32(TCNTO4, val);
            val &= 0xFFFF;

            diff = prev - val;
            if (diff != 0) {
                if(diff < 0)
                    diff += (CYGNUM_HAL_RTC_PERIOD+1);

                break;  // atleast 1 tick has passed
            } 
        }
        prev = val;
        ticks += diff;
    }
}

// -------------------------------------------------------------------------

// This routine is called to respond to a hardware interrupt (IRQ).  It
// should interrogate the hardware and return the IRQ vector number.
int 
hal_IRQ_handler(void)
{
    cyg_uint32 ior;

    HAL_READ_UINT32(INTOFFSET, ior);
    return (int)ior;
}

//----------------------------------------------------------------------------
// Interrupt control

void
hal_interrupt_mask(int vector)
{
    cyg_uint32 imr;

    CYG_ASSERT(vector <= CYGNUM_HAL_ISR_MAX &&
               vector >= CYGNUM_HAL_ISR_MIN , "Invalid vector");

    HAL_READ_UINT32(INTMSK, imr);
    imr |= (1<<vector);
    HAL_WRITE_UINT32(INTMSK, imr);
}

void
hal_interrupt_unmask(int vector)
{
    cyg_uint32 imr;

    CYG_ASSERT(vector <= CYGNUM_HAL_ISR_MAX &&
               vector >= CYGNUM_HAL_ISR_MIN , "Invalid vector");

    HAL_READ_UINT32(INTMSK, imr);
    imr &= ~(1<<vector);
    HAL_WRITE_UINT32(INTMSK, imr);
}

void
hal_interrupt_acknowledge(int vector)
{
    cyg_uint32 ipr;

    CYG_ASSERT(vector <= CYGNUM_HAL_ISR_MAX &&
               vector >= CYGNUM_HAL_ISR_MIN , "Invalid vector");

    HAL_WRITE_UINT32(SRCPND, (1<<vector));
    HAL_READ_UINT32(INTPND, ipr);
    HAL_WRITE_UINT32(INTPND, ipr);
}

void
hal_interrupt_configure(int vector, int level, int up)
{
    CYG_ASSERT(vector <= CYGNUM_HAL_ISR_MAX &&
               vector >= CYGNUM_HAL_ISR_MIN, "Invalid vector");
}

void hal_interrupt_set_level(int vector, int level)
{
    CYG_ASSERT(vector <= CYGNUM_HAL_ISR_MAX &&
               vector >= CYGNUM_HAL_ISR_MIN, "Invalid vector");
}


//-----------------------------------------------------------------------------
// End of som2416_misc.c
