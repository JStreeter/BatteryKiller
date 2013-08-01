/* 
 * File:   main.c
 * Author: Discordia
 *
 * Created on July 27, 2013, 3:27 PM
 */

#include    <stdio.h>
#include    <stdlib.h>
#include    <GenericTypeDefs.h>
#include    <p24Fxxxx.h>
#include    <uart.h>
#include    <adc.h>
#include    <timer.h>

#include    "./Setups.h"
#include    "./Gloabals.h"

_FBS( BWRP_OFF & BSS_OFF )
_FOSCSEL( FNOSC_FRC & SOSCSRC_ANA & IESO_OFF & LPRCSEL_HP )
_FOSC( POSCMOD_HS & OSCIOFNC_OFF & FCKSM_CSECMD & SOSCSEL_SOSCLP )
_FWDT( WDTPS_PS32768 & FWPSA_PR128 & FWDTEN_OFF & WINDIS_OFF )
_FPOR( BOREN_BOR0 & PWRTEN_OFF & I2C1SEL_PRI & BORV_V20 & MCLRE_ON )//MCLRE IS FUCKING ON!!!!!
_FICD( ICS_PGx1 )
_FDS( DSWDTPS_DSWDTPS5 & DSWDTOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF );

/*
 * 
 */


int main(int argc, char** argv)
{
    DWORD SampleCount,i;
    //Speed
    CLKDIVbits.RCDIV = 0;           //Default is 4 Mhz... This iS 8 Mhz
    __builtin_write_OSCCONH(0x01);  //Change the secondary clock to 8MHz with Pll
    __builtin_write_OSCCONL(0x01);  //GO GO Gadget Change
    OSCCONbits.OSWEN = 1;           //GO GO Clock clock switch
    Nop();                          //Tiny delay
    while(OSCCONbits.OSWEN);        //While the clock switch is not complete ... Wait
    //End of Speed

    UART1_Config();//115200 8n1 Idle high
    Setup_12bit_A2D();// duh
    InitChip();//Setup gloabals and what not

    SampleCount = 0; // Geniric sample counter incase of Resets

    //Clean the buffer
    ReadADC10(0);
    ReadADC10(1);
    ReadADC10(12);
    ReadADC10(11);
    ReadADC10(14);
    ReadADC10(15);

    SetChanADC10( ADC_CH0_POS_SAMPLEA_AN0 & ADC_CH0_NEG_SAMPLEA_VREFN );//Make sure it is pointing to the lowest one

    IFS0bits.AD1IF = 0;//Reload the Round

    TimerSetup();//After the first proc it fires the A2D

    for(i = 6500000;i>1;i--);
    for(i = 6500000;i>1;i--);
    for(i = 6500000;i>1;i--);
    for(i = 6500000;i>1;i--);
    for(i = 6500000;i>1;i--);
    for(i = 6500000;i>1;i--);

    T1CONbits.TON = 1;
    while(1)
    {
        IFS0bits.AD1IF = 0;//Reload the Round
        printf("%lu,",SampleCount++);//Good use of time to print counter
        while(IFS0bits.AD1IF != 1);//Waiting for all the conversions to finish
        printf("%d,%u,%u,%u,%d,%u,%u,%u,\n",LowI_Line,ReadADC10(0),ReadADC10(1),ReadADC10(14),
                                        HighI_Line,ReadADC10(15),ReadADC10(12),ReadADC10(11));//And PRINT
       
    }//AGAIN

    return (EXIT_SUCCESS);//Required for mplabx
}//Main finished
