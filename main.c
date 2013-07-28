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
#include    <PIC24F_periph_features.h>
#include    <adc.h>
#include    <math.h>
#include    <libq.h>

//#include    "/Setups.h"
#include    "./Setups.h"
_FBS(BWRP_OFF & BSS_OFF )
_FOSCSEL( FNOSC_FRC & IESO_OFF )
_FOSC( POSCMOD_HS & OSCIOFNC_OFF & FCKSM_CSECMD & SOSCSEL_SOSCLP )
_FWDT( WDTPS_PS32768 & FWPSA_PR128 & FWDTEN_OFF & WINDIS_OFF )
_FPOR( BOREN_BOR0 & PWRTEN_OFF & I2C1SEL_PRI & BORV_V20 & MCLRE_ON )
_FICD( ICS_PGx1 )
_FDS( DSWDTPS_DSWDTPS5 & DSWDTOSC_LPRC & DSBOREN_OFF & DSWDTEN_OFF )
/*
 * 
 */
int main(int argc, char** argv)
{
    DWORD i;
    WORD RawA2D;
    //Speed
    CLKDIVbits.RCDIV = 0;           //Default is 4 Mhz... This iS 8 Mhz
    __builtin_write_OSCCONH(0x01);  //Change the secondary clock to 8MHz with Pll
    __builtin_write_OSCCONL(0x01);  //GO GO Gadget Change
    OSCCONbits.OSWEN = 1;           //GO GO Clock clock switch
    Nop();                          //Tiny delay
    while(OSCCONbits.OSWEN);        //While the clock switch is not complete ... Wait
    //End of Speed

    UART1_Config();
    Setup_12bit_A2D();
    printf("Good morning Master\r\n");

    while(1)
    {
        AD1CON1bits.SAMP = 1;
        while(!AD1CON1bits.DONE);
        RawA2D = ReadADC10(0);
        printf("%u\r\n",RawA2D);
        for(i = 0; i<5000;i++);
    }

    return (EXIT_SUCCESS);
}
