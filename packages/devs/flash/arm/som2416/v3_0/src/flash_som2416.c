//==========================================================================
//
//      flash_som2416.c
//
//      som2416 nand flash  driver
//
//==========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
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
// Author(s):    Gary Thomas <gary@mlbassoc.com>
// Contributors: 
// Date:         2003-09-02
// Purpose:
// Description:  FLASH drivers for Toshiba NAND FLASH TC58xxx devices.
//               Based on Atmel AT49xxxx drivers by Jani Monoses <jani@iv.ro>
//
//####DESCRIPTIONEND####
//
//==========================================================================

// FIXME!  Someday add support for ECC data & fixups of bad sectors

#include <pkgconf/hal.h>
#include <cyg/hal/hal_arch.h>
#include <cyg/hal/hal_cache.h>
#include <cyg/infra/diag.h>
#include CYGHWR_MEMORY_LAYOUT_H

#define  _FLASH_PRIVATE_
#include <cyg/io/flash.h>

#define CYGNUM_FLASH_BLANK	(1)
#define CYGNUM_FLASH_INTERLEAVE (1)
#define CYGNUM_FLASH_SERIES     (1)
#define CYGNUM_FLASH_WIDTH      (8)
//#define CYGNUM_FLASH_BASE       (0xFE000000)

//----------------------------------------------------------------------------
// Now that device properties are defined, include magic for defining
// accessor type and constants.
#include <cyg/io/flash_dev.h>

#include <cyg/hal/s3c2416.h>
#include <som2416_nand.h>

#if 0
#define	flash_printf(str,args...) diag_printf("\nFunc:%s,Line:%d->"str,__FUNCTION__,__LINE__,##args)
#else
#define	flash_printf(str,args...) {}
#endif

#define KEPT_BLOCKS  4 
           //Block0:nboot; Block1..2:Redboot; start from Block3; Block3,
    		//empty block; used to notify nboot the load process was over.

//----------------------------------------------------------------------------
// Initialize driver details
int
flash_hwr_init(void)
{
    flash_data_t id[4];
    int i;

	NF8_Init();
	
    flash_dev_query(id);

    // Check that flash_id data is matching the one the driver was
    // configured for.

    // Check manufacturer
    if (id[0] != 0xec) {		//0xec, samsung maker code
        flash_printf("Can't identify FLASH - manufacturer is: %x, should be %x\n", 
                    id[0], 0xec);
        return FLASH_ERR_DRV_WRONG_PART;
    }

    // Did we find the device? If not, return error.
    if (id[1]!=0xda) {
        diag_printf("Can't identify FLASH - device is: %x ", id[1]);
        diag_printf("\n");
        return FLASH_ERR_DRV_WRONG_PART;
    }

    // Fill in device details
    flash_info.block_size = BYTES_PERBLOCK;
    flash_info.blocks = BLOCKS_INNAND;
    flash_info.start = (void *)(BYTES_PERBLOCK*KEPT_BLOCKS);	
    flash_info.end = (void *)(BLOCKS_INNAND*BYTES_PERBLOCK);
    return FLASH_ERR_OK;
}

//----------------------------------------------------------------------------
// Map a hardware status to a package error
int
flash_hwr_map_error(int e)
{
	return e;
//       return FLASH_ERR_PROGRAM;
//       return FLASH_ERR_ERASE;
//       return FLASH_ERR_HWR;  // FIXME
//       return FLASH_ERR_OK;

}


//----------------------------------------------------------------------------
// See if a range of FLASH addresses overlaps currently running code
bool
flash_code_overlaps(void *start, void *end)
{
//    extern unsigned char __stext[], __etext[];	//defined by the linker
//    extern unsigned char edata[]; //defined by the linker(target.ld). 
    
	//cyg_halint32 codeblocks= (((unsigned int)edata-0x00100000)/BYTES_PERBLOCK)+2; //blocks of code space, include nboot space	
//	if(start < (codeblocks*BYTES_PERBLOCK))
	if(start < (BYTES_PERBLOCK*KEPT_BLOCKS))
		return true;
	else
		return false;
}

#define BLOCK_ADR(x) (x>>17)	//x/128K
#define PAGE_ADR(x)  ((x&0x1ffff)>>11)	//2048 bytes 
#define BYTE_ADR_INPAGE(x)  (x&0x7ff)	//
//----------------------------------------------------------------------------
// Erase Block
int
flash_erase_block(void* iblock, unsigned int size)
{
	cyg_uint32 block=(cyg_uint32)iblock;
	//block was address of bytes; size was blocksize, nouse;
	if(block<BYTES_PERBLOCK)
		return FLASH_ERR_INVALID;
	flash_printf("erase block adr:0x%x; Block:0x%x\n",block,BLOCK_ADR(block));
	if(Adv_NF8_EraseBlock(BLOCK_ADR(block))==OK)
		return FLASH_ERR_OK; //128k; 2^17
	else
		return FLASH_ERR_ERASE;
}


//----------------------------------------------------------------------------
// Program Buffer a region of flash
int
flash_program_buf(void* iaddr, void* data, int len)
{
	cyg_uint32 i;	//len /2048
	cyg_uint32 start_page;
	cyg_uint32 addr=(cyg_uint32)iaddr;
	void * p=data;
	cyg_uint32 blockadr=BLOCK_ADR(addr);
	cyg_uint32 writecount=0;

	flash_printf("iaddr:0x%x, pdata:0x%x, len:0x%x\n",iaddr,data,len);
	
    if(addr<flash_info.start)
		return FLASH_ERR_INVALID;

	//start page
	start_page=PAGE_ADR(addr);
	
	for(i=0;i<PAGES_PERBLOCK;i++){
		if(Adv_NF8_WritePage(blockadr,i+start_page,p)==FAIL)
			return FLASH_ERR_PROGRAM;
		p+=BYTES_PERPAGE;
		writecount+=BYTES_PERPAGE;
		if(writecount>=len)
			break;
	}
	flash_printf("write: 0x%x bytes!\n",writecount);
	return FLASH_ERR_OK;
}

//only enabled when:    requires      { CYGSEM_IO_FLASH_READ_INDIRECT == 1 }
//----------------------------------------------------------------------------
// Read data into buffer
int
flash_read_buf(void* iaddr, void* data, int len)
{
	cyg_uint32 addr=(cyg_uint32)iaddr;
	cyg_uint32 i;	//len /2048
	cyg_uint32 blockadr=BLOCK_ADR(addr);
	cyg_uint32 start_page;
	void * p=data;
	cyg_uint32 readcount=0;
	
    if(addr<flash_info.start)
		return FLASH_ERR_INVALID;
  	//start page
	start_page=PAGE_ADR(addr);
	
	for(i=0;i<PAGES_PERBLOCK;i++){
		if(Adv_NF8_ReadPage(blockadr,i+start_page,p)==FAIL)
			return FLASH_ERR_DRV_TIMEOUT;
		p+=BYTES_PERPAGE;
		readcount+=BYTES_PERPAGE;
		if(readcount>=len)
			break;
	}
	return FLASH_ERR_OK;
}

int flash_query(unsigned char *data) __attribute__ ((section (".2ram.flash_query")));

int
flash_query(unsigned char *data)
{
	cyg_halint16 id;
	id=NF8_CheckId();
    *data++ = id>>8;  // Manufacturer code
    *data++ = id & 0xff;  // Device identifier
    return FLASH_ERR_OK;
}

