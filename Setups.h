/* 
 * File:   Setups.h
 * Author: Discordia
 *
 * Created on July 27, 2013, 7:17 PM
 */

#ifndef SETUPS_H
#define	SETUPS_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define __FOSC_ 32000000
#define __FTCY_ (__FOSC_/2)
#define __U1BAUD_ 115200L //<--- Desired Baud rate UART1 CHANGE THIS
#define __BAUDUART1_ ((__FTCY_/(4*__U1BAUD_))-1)

void UART1_Config(void);
void Setup_12bit_A2D(void);
void TimerSetup(void);
void InitChip(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SETUPS_H */

