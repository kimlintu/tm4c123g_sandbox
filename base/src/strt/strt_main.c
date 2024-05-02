/*********************************************************** 
 *
 * Group:  STRT - Startup
 * Module: Main - Main entry point
 * 
 * This module contains the startup code, the first
 * code executed after the we exit the boot.
 * 
 ***********************************************************/
#include <stdint.h>

#include "strt_main.h"
#include "strt_vect.h"

extern uint32_t _lnk_romDataSectionStart_U32;
extern uint32_t _lnk_ramDataSectionStart_U32;
extern uint32_t _lnk_dataSectionSize_U32;

extern uint32_t _lnk_ramBssSectionStart_U32;
extern uint32_t _lnk_bssSectionSize_U32;

extern int32_t main(void);

void Strt_main(void)
{
    uint32_t i_U32;
    uint32_t *romDataSection_pU32 = &_lnk_romDataSectionStart_U32;
    uint32_t *ramDataSection_pU32 = &_lnk_ramDataSectionStart_U32;
    uint32_t dataSectionSize_U32  = ((uint32_t)&_lnk_dataSectionSize_U32) / sizeof(uint32_t);
    uint32_t *ramBssSection_pU32  = &_lnk_ramBssSectionStart_U32;
    uint32_t bssSectionSize_U32   = ((uint32_t)&_lnk_bssSectionSize_U32) / sizeof(uint32_t);

    /* Copy .data section */    
    for (i_U32 = 0; i_U32 < dataSectionSize_U32; i_U32++)
    {
        ramDataSection_pU32[i_U32] = romDataSection_pU32[i_U32];
    }

    /* Copy .bss section  */
    for (i_U32 = 0; i_U32 < bssSectionSize_U32; i_U32++)
    {
        ramBssSection_pU32[i_U32] = 0;
    }

    Vect_updateVectorTableOffset();

    /* Call main application */
    main();
}