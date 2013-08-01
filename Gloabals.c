#include    <p24Fxxxx.h>
#include    <GenericTypeDefs.h>
#include    <stdio.h>

#include    "./Setups.h"
#include    "./Gloabals.h"

DWORD A2DSAMPLINGTIME;
DWORD HighI_OnTime;
DWORD HighI_OffTime;
DWORD LowI_OnTime;
DWORD LowI_OffTime;

void InitChip()
{
    A2DSAMPLINGTIME = 250;//ms
    HighI_OnTime    = 3000;//3 secs on
    HighI_OffTime   = 297000;//Rest of the 5min off
    LowI_OnTime     = 240000;//4 min on
    LowI_OffTime    = 30000;//30sec off
//    HighI_OnTime    = 3000;//3 secs on
//    HighI_OffTime   = 57000;//Rest of the 5min off
//    LowI_OnTime     = 5000;//4 min on
//    LowI_OffTime    = 5000;//30sec off

    LowI_Line = 0;
    TRISBbits.TRISB15 = 0;//LowI
    HighI_Line = 0;
    TRISBbits.TRISB14 = 0;

    printf("IntChip is Green\n");
    return;
}
