#include <stdint.h>
#include <xc.h>
#include "timer0.h"

//Init timer 0 with internal clock and prescaler 1:1
void InitTMR0 (){
    TMR0 = 0;
    OPTION_REGbits.T0CS = 0; //Timer clock = internal clock
    OPTION_REGbits.PSA = 1; //Prescaler to WDT
}

//Enable TMR 0 interrupt for 1 second delay
void initSecondDelay (){
    secondCounter = 0;
    oneSecF = false;
    TMR0 = 0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
}

//calls number of seconds delay
void SecsDelay (uint8_t seconds){
    for (uint8_t second = 0; second < seconds;++second){
        initSecondDelay();
        while (oneSecF == false);
    }
}

//Delay 20-30 ms after button pressed
void DebounceIO () {
    TMR0 = DebTime; //value for 20-30 ms delay
    INTCONbits.T0IF = 0; //Clear timer 0 overflow flag.
    while (INTCONbits.T0IF == 0); //Wait for timer 0 overflow flag to set
}
