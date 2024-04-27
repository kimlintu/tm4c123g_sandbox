#include <stdint.h>

#include "startup.h"

extern uint32_t _lnk_romDataSectionStart_U32;
extern uint32_t _lnk_ramDataSectionStart_U32;
extern uint32_t _lnk_dataSectionSize_U32;

extern uint32_t _lnk_ramBssSectionStart_U32;
extern uint32_t _lnk_bssSectionSize_U32;

extern int32_t main(void);

void startup(void)
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

    /* Call main application */
    main();
}