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

#define __FOSC_ 32000000
#define __FTCY_ (__FOSC_/2)
#define __U1BAUD_ 115200L //<--- Desired Baud rate UART1 CHANGE THIS
#define __BAUDUART1_ ((__FTCY_/(4*__U1BAUD_))-1)

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
 //  inline void Chip_Go_Fast(void);
    CLKDIVbits.RCDIV = 0;

    __builtin_write_OSCCONH(0x01);//Change the secondary clock to 8MHz with Pll
    __builtin_write_OSCCONL(0x01);//GO GO Gadget Change

   // while(OSCCONbits.CLKLOCK != 1 );

    void UART1_Config(void);
    UART1_Config();
   // printf("Hello World\r\n");
    DWORD i;
    ANSA = 0;
    ANSB = 0;

    TRISA = 0;
    TRISB = 0;
    while(1)
    {
        //LATA ^= 0xFFFF;
        //LATB ^= 0xFFFF;
        printf("Hello World\r\n");
        for(i = 0; i<1000;i++);
    }
    while(1);

    return (EXIT_SUCCESS);
}

void UART1_Config(void){

    OpenUART1((
            UART_EN &                   //Enable UART Module
            UART_IDLE_CON &             //Work while idle
            UART_IrDA_DISABLE &         //Disable Infared decoder
            UART_MODE_SIMPLEX &         //UART Simplex mode (RTS pin)
            UART_UEN_00 &               //TX/RX pins configured all other latched
            UART_DIS_WAKE &             //Disable wake on Start bit
            UART_DIS_LOOPBACK &         //Disable loopback
            UART_DIS_ABAUD &            //Disable Auto Baud
            UART_UXRX_IDLE_ONE &        //Receive idle is 1
            UART_BRGH_FOUR &         //16 clocks per bit period
            UART_NO_PAR_8BIT &          //No parity bit
            UART_1STOPBIT               //One stop bit
            ),
            (
            UART_INT_TX_LAST_CH &       //Interrupt when last character shifted out
            UART_IrDA_POL_INV_ZERO &    //IrDA encoded, UxTX Idel state is '0'
            UART_SYNC_BREAK_DISABLED &  //Sync break transmission disabled or completed
            UART_TX_ENABLE &            //Transmit enable
           // UART_TX_BUF_NOT_FUL &       //Transmit buffer is not full
            UART_INT_RX_CHAR &          //Interrupt on every char received
            UART_ADR_DETECT_DIS &       //address detect disable
            UART_RX_OVERRUN_CLEAR       //Rx buffer Over run status bit clear
            ),
            (
            __BAUDUART1_ //Baud rate
            ));
    ConfigIntUART1(
                UART_RX_INT_DIS &        //Receive interrupt disabled
                UART_RX_INT_PR1 &       //Priority RX interrupt 1
                UART_TX_INT_DIS &       //transmit interrupt disabled
                UART_TX_INT_PR2         //Priority TX interrupt 1
            );



#ifdef InvertU1RxTxBits
    U1STAbits.UTXINV = 0;
    U1MODEbits.URXINV = 0;
#endif

    //Set the tristate and map pins for Uart
//    TRIS_U1TX;
//    TRIS_U1RX;
//    MAP_U1TX;
//    MAP_U1RX;
}