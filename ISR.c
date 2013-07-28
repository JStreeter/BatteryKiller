#include    <p24Fxxxx.h>
#include    <timer.h>
#include    "./Gloabals.h"

void __attribute__ ((auto_psv))     _ISR    _T1Interrupt(void)
{
    _T1IF = 0;          //clear interrupt flag
    static DWORD Tick = 0;
    static DWORD NextA2DSample=1, NextLowCurrentToggle=1,NextHighCurrentToggle=1;
    Tick++;//Tick

    if(Tick == NextA2DSample)
    {
        NextA2DSample += A2DSAMPLINGTIME;
        FireA2D;
    }

    if(Tick == NextLowCurrentToggle)
    {
        if(LowI_Line)//Was on
        {
            NextLowCurrentToggle += LowI_OffTime;
            LowI_Line = 0;//Now Off
        }
        else//was off
        {
            NextLowCurrentToggle += LowI_OnTime;
            LowI_Line = 1;//now on
        }
    }
    if(Tick == NextHighCurrentToggle)
    {
        if(HighI_Line)//Was on
        {
            NextHighCurrentToggle += HighI_OffTime;
            HighI_Line = 0;//Now Off
        }
        else//was off
        {
            NextHighCurrentToggle += HighI_OnTime;
            HighI_Line = 1;//now on
        }
    }
    return;
}
