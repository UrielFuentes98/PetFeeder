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
#pragma config MCLRE = OFF       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>
#include <stdint.h> 
#include "timer0.h"
#include "PWM.h"
#include "GPIOs.h"
#include "timer1.h"
#include "ADC.h"

volatile bool progFinish = false; 
enum states {TIMER, PROGRAMMING, FEEDING};
frequencies frequecy = ONCE_D;
enum states STATE = TIMER;

void FeedPet (void);
void stateMachine (void);
void checkPushB (void);

void main(void) {
    
    OSCCONbits.IRCF = 0; //Setting 31 kHz clock frequency
    INTCONbits.GIE = 1; //Enabling interrupts
    InitTMR0();
    PWMInit();
    initGPIOs();
    initTMR1 ();
    initADC0();
    
    while(1){
        stateMachine ();
        checkPushB ();
    }
}

//Move servor forth and back
void FeedPet (){
    setPWM_DC (DUTY_5);
    SecsDelay (2);
    setPWM_DC (DUTY_7);
    SecsDelay (2);
    TRISIO2 = 1;
}

//Check current state and execute appropiate action
void stateMachine (void){
switch (STATE){
    
    case TIMER:
        //Checks if timer1 counter reached maximun to change state
        if (Hours == HoursTarget){
            STATE = FEEDING;
        } 
        break;
        
    case PROGRAMMING:
        //Check if programming timeout ocurred
        if (progFinish){
            STATE = FEEDING;
        }else{
            //Read ADC value to update feeding frequency
            frequecy = getFreq();
        }
        break;
        
    case FEEDING:
        //Turn leads off, reset timer 1 to start 
        //count and update feeding frequency
        T1CONbits.TMR1ON = 0; //Disables timer 1
        turnOffLEDs();
        FeedPet();
        ResetTime();
        updateWaitTime (frequecy);
        STATE = TIMER;
        break;  
        
    }    
}

//Check for push button push
void checkPushB (void){
    //Checks if Push button was pressed
    if (INTCONbits.GPIF){
        if (GP3){
            if (STATE == TIMER){
                //If in timer mode change to programming and start 
                //programming timeout
                STATE = PROGRAMMING;
                progFinish = false;
                ResetTime();
            }else if (STATE == PROGRAMMING){
                STATE = FEEDING;
            }
            DebounceIO();
        }
        INTCONbits.GPIF = 0;
    }
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
    }else if (PIE1bits.TMR1IE && PIR1bits.TMR1IF){
        switch (STATE){
            case TIMER:
                if (Halfminutes < HalfminsHour){
                    Halfminutes ++;
                }else{
                    Halfminutes = 0;
                    Hours ++;
                }
                break;
            case PROGRAMMING:
                progFinish = true;
                break;
        }
        PIR1bits.TMR1IF = 0;
        TMR1H = HalfMinTMR1HVal;
    }
    
}
