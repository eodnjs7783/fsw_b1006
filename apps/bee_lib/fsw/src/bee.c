#include <cfe.h>
#include <BEE/bee.h>

int32 HVD_LibInit(void)
{
    BEE_LoadOpts();
    BEE_SetRunStatusOn(BEE_RUNSTATUS_LIB);
    OS_printf ("BEE Lib Initialized.\n");
                
    return OS_SUCCESS;
}
