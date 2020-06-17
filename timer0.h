/* 
 * File:   timer0.h
 * Author: uriel
 *
 * Created on June 16, 2020, 6:06 PM
 */

#ifndef TIMER0_H
#define	TIMER0_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>
    
typedef enum { false, true } bool;

#define DebTime 100 //Timer value for debounce delay
#define oneSecCount 30 //Counter value for 1 sec period

volatile bool oneSecF = false;
volatile uint8_t secondCounter = 0;

void InitTMR0 (void);
void DebounceIO (void);
void initSecondDelay (void);
void SecsDelay (uint8_t seconds);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER0_H */

