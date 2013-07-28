#include    <GenericTypeDefs.h>
#include    <p24Fxxxx.h>
#include    <uart.h>
#include    <adc.h>
#include    "./Setups.h"


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
            UART_BRGH_FOUR &         //4 clocks per bit period(High Speed)
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
            __BAUDUART1_ //Baud rate defined in Setups.h
            ));
    ConfigIntUART1(
                UART_RX_INT_DIS &        //Receive interrupt disabled
                UART_RX_INT_PR1 &       //Priority RX interrupt 1
                UART_TX_INT_DIS &       //transmit interrupt disabled
                UART_TX_INT_PR2         //Priority TX interrupt 2
            );

#ifdef InvertU1RxTxBits
    U1STAbits.UTXINV = 0;
    U1MODEbits.URXINV = 0;
#endif
    //Set the tristate and map pins for Uart
    TRISBbits.TRISB7 = 0;//    TRIS_U1TX;
    TRISBbits.TRISB2 = 1;//    TRIS_U1RX;
    ANSBbits.ANSB2 = 0;// Made it digital

    return;
}

void Setup_12bit_A2D()
{

    return;
}