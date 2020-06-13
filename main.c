/*
 * File:   main.c
 * Author: uriel
 *This is the program to activate a Servo Motor in a certain period of time 
 *for a pet peeder device.
 * Created on June 12, 2020
 */


// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>

#define DUTY_5 31 // 5% - 31 
#define DUTY_10 60 //10% - 60
#define Freq50 142 //with formula should 154, but after calibration 142

void PWMInit () {
    TRISIO2 = 1; //Desabling CCP module output. 
    PR2 = Freq50; 
    CCP1CONbits.CCP1M = 0b1100; //Selecting PWM mode.
    CCP1CONbits.DC1B = DUTY_5 & 3; //lower two bits.
    CCPR1L = DUTY_5 >> 2;  //Upper bits. 
    PIR1 &= 0xFD; //clearing timer 2 flag
    T2CON = 0b100; //enabling timer 2 with 0 post and prescaler. 
    while (!(PIR1 & 0x2)); //wait for timer flag to set before activating PWM.
    TRISIO2 = 0; //Enabling CCP output. 
}

void main(void) {
    
    OSCCONbits.IRCF = 0; //Setting 31 kHz clock frequency
    PWMInit();
    while(1);
    
}
