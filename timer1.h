/* 
 * File:   timer1.h
 * Author: uriel
 *
 * Created on June 18, 2020, 11:54 AM
 */

#ifndef TIMER1_H
#define	TIMER1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>
#include "ADC.h"

#define HalfMinTMR1HVal  0x99
#define HalfminsHour 120
#define hrsToMove1 24
#define hrsToMove2 12
#define hrsToMove3 8

volatile uint8_t HoursTarget = 0;
volatile uint8_t Hours = 0;
volatile uint8_t Halfminutes = 0;
void initTMR1 (void);
void ResetTime (void);
void updateWaitTime (frequencies newFreq);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

