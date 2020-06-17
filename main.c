/*
 * File:   main.c
 * Author: uriel
 *This is the program to activate a Servo Motor in a certain period of time 
 *for a pet peeder device.
 * Created on June 12, 2020
 */


// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>
#include <stdint.h> 
#include "timer0.h"
#include "PWM.h"

void FeedPet (void);

void main(void) {
    
    OSCCONbits.IRCF = 0; //Setting 31 kHz clock frequency
    INTCONbits.GIE = 1; //Enabling interrupts
    InitTMR0();
    PWMInit();
    while(1){
        FeedPet();
    }
}

//Move servor forth and back
void FeedPet (){
    setPWM_DC (DUTY_10);
    SecsDelay (2);
    setPWM_DC (DUTY_7);
    SecsDelay (2);
}

//Interrupt to reach one second delay with timer 0
void __interrupt () Timer0_ISR (void){
    
    if (INTCONbits.T0IE && INTCONbits.T0IF){
        INTCONbits.T0IF = 0;
        if (secondCounter < oneSecCount){    
            ++secondCounter;
        }else{
            //One second pass. Disable interrupt set flag
            oneSecF = true;
            INTCONbits.T0IE = 0;
        }
    }
    
}
