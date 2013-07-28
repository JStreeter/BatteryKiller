#include    <GenericTypeDefs.h>
#include    <p24Fxxxx.h>
#include    <uart.h>
#include    <adc.h>
#include    <timer.h>
#include    <stdio.h>

#include    "./Setups.h"
#include    "./Gloabals.h"

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

    printf("UART is Green\n");
    return;
}

void Setup_12bit_A2D()
{

    ANSAbits.ANSA0 = 1;
    ANSAbits.ANSA1 = 1;
    ANSAbits.ANSA2 = 1;
    ANSAbits.ANSA3 = 1;
    ANSBbits.ANSB4 = 1;
    ANSBbits.ANSB12 = 1;

    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    TRISAbits.TRISA2 = 1;
    TRISAbits.TRISA3 = 1;
    TRISBbits.TRISB4 = 1;
    TRISBbits.TRISB12 = 1;

    OpenADC10(
            (
                ADC_MODULE_ON   &    /*A/D Converter on */
                ADC_IDLE_STOP   &     /* A/D Stop in Idle mode */
                ADC_12BIT_MODE  &
                ADC_FORMAT_INTG &
                ADC_TRIG_AUTO   &
                ADC_AUTO_SAMPLING_OFF &
                ADC_SAMP_OFF
            ),
            (
                ADC_POS_VREF_INT_VRH2   & //4 * BandGap reference... Needs >4.5 volts for the thing to work
                ADC_NEG_VREF_AVSS       &
                ADC_BUF_REG_ENABLE      &
                ADC_OFFSET_CAL_OFF      &
                ADC_SCAN_ON             &
                ADC_INTR_6_CONV         & //soon
                ADC_ALT_BUF_OFF         &
                ADC_ALT_INPUT_OFF
            ),
            (
                ADC_CONV_CLK_INTERNAL_RC    &
                ADC_SAMPLE_TIME_31          &
                ADC_CONV_CLK_42Tcy
            ),
            (
                ADC_AUTO_SCAN_ENABLE   &
                ADC_LOW_POWER_DISABLE   &
                ADC_CTMU_DISABLE        &
                ADC_BG_ENABLE           &
                ADC_WRITE_LEGACY        &
                ADC_CMP_LESS_MODE
            ),
            (
              0 //Skips All //AD1CTMUENL
            ),
            (
               0//Skips All //AD1CTMUENH
            ),
            (
                ADC_SCAN_AN0 &
                ADC_SCAN_AN1 &
                ADC_SKIP_SCAN_AN2 &
                ADC_SKIP_SCAN_AN3 &
                ADC_SKIP_SCAN_AN4 &
                ADC_SKIP_SCAN_AN5 &
                ADC_SKIP_SCAN_AN6 &
                ADC_SKIP_SCAN_AN7 &
                ADC_SKIP_SCAN_AN8 &
                ADC_SKIP_SCAN_AN9 &
                ADC_SKIP_SCAN_AN10 &
                ADC_SKIP_SCAN_AN11 &
                ADC_SCAN_AN12 &
                ADC_SCAN_AN13 &
                ADC_SCAN_AN14 &
                ADC_SCAN_AN15
            ),
            (
                ADC_SKIP_SCAN_AN16 &
                ADC_SKIP_SCAN_AN17 &
                ADC_SKIP_SCAN_AN26 &
                ADC_SKIP_SCAN_AN27 &
                ADC_SKIP_SCAN_AN28 &
                ADC_SKIP_SCAN_AN29 &
                ADC_SKIP_SCAN_AN30
            )
    );


    printf("A2D is Green\n");
    return;
}

void TimerSetup(void)
{
    OpenTimer1(
            (
            T1_ON &
            T1_IDLE_CON &
            T1_GATE_OFF &
            T1_PS_1_64 &
            T1_SYNC_EXT_OFF &
            T1_SOURCE_INT
            ),
            TIMERONEPERIOD);          //every .001sec
    printf("Timer1 is Green\n");
    ConfigIntTimer1(T1_INT_PRIOR_1 & T1_INT_ON);

    return;
}
