/* 
 * File:   Gloabals.h
 * Author: Discordia
 *
 * Created on July 28, 2013, 2:38 PM
 */

#ifndef GLOABALS_H
#define	GLOABALS_H

#ifdef	__cplusplus
extern "C"
{
#endif

#define FireA2D AD1CON1bits.SAMP = 1

typedef enum{
    OFF = 0,
    ON = 1
}LINESTATE;

//in seconds
#define LINE1_ON_TIME    1
#define LINE1_OFF_TIME    1
#define LINE2_ON_TIME    1
#define LINE2_OFF_TIME    1

void UserChangeSampleRate (void);

//double Rate1;          //initialize 1 second
//double Rate2;          //initialize 1 second
//WORD NetRate1;        //initialize 1 second
//WORD NetRate2;        //initialize 1 second
//WORD ProcCount;

#define HighCurrentLine
#define LowI_Line  LATBbits.LATB15
#define HighI_Line  LATBbits.LATB14

extern DWORD A2DSAMPLINGTIME;//ms
extern DWORD HighI_OnTime;
extern DWORD HighI_OffTime;
extern DWORD LowI_OnTime;
extern DWORD LowI_OffTime;

#define TIMERONEPERIOD  125
/*
 * minimum sample rate  : 50 hz, .02 s;
 * maximum sample rate  : 5 minutes, 300s;
 *
 * timer proc rate at 63 prescale  : 0.000008s;
 * period at                        : 125;
 * 125 * 0.000008 = .001
 * 1 ms Proc
 * QED
 */
#ifdef	__cplusplus
}
#endif

#endif	/* GLOABALS_H */

