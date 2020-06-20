#include <stdint.h>
#include <xc.h>
#include "timer1.h"
#include "ADC.h"

void initTMR1 (void){
    T1CONbits.TMR1CS = 0; //TMR 1 clk, system clk
    T1CONbits.T1CKPS = 0b11; //TMR 1 prescaler = 8
    TMR1H = HalfMinTMR1HVal;
    TMR1L = 0;
    T1CONbits.TMR1ON = 1; //Enables timer 1
    T1CONbits.TMR1GE = 0; //Ignores gate
    PIE1bits.TMR1IE = 1; //Enables timer 1 interrupt
    INTCONbits.PEIE = 1; //Enables peripheral interrupts
    PIR1bits.TMR1IF = 0; //Clears timer 1 overflow flag
}

void ResetTime (void){
    Halfminutes = 0;
    Hours = 0;
    TMR1H = HalfMinTMR1HVal;
    T1CONbits.TMR1ON = 1; //Enables timer 1
}

void updateWaitTime (frequencies newFreq){
    switch(newFreq){
        case ONCE_D:
            HoursTarget = hrsToMove1;
            break;
        case TWICE_D:
            HoursTarget = hrsToMove2;
            break;
        case THREE_D:
            HoursTarget = hrsToMove3;
    }   
}