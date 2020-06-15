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

typedef enum { false, true } bool;
#define DUTY_5 31 // 5% - 31 
#define DUTY_10 60 //10% - 60
#define Freq50 142 //with formula should 154, but after calibration 142
#define DebTime 100 //Timer value for debounce delay
#define oneSecCount 30 //Counter value for 1 sec period

volatile uint8_t secondCounter = 0;
volatile bool oneSecF = false;


//Init timer 0 with internal clock and prescaler 1:1
void InitTMR0 (){
    TMR0 = 0;
    OPTION_REGbits.T0CS = 0; //Timer clock = internal clock
    OPTION_REGbits.PSA = 1; //Prescaler to WDT
}

//Delay 20-30 ms after button pressed
void DebounceIO () {
    TMR0 = DebTime; //value for 20-30 ms delay
    INTCONbits.T0IF = 0; //Clear timer 0 overflow flag.
    while (INTCONbits.T0IF == 0); //Wait for timer 0 overflow flag to set
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

//Change PWM duty cycle
void setPWM_DC (uint8_t DutyCycle){
    CCP1CONbits.DC1B = DutyCycle & 3; //lower two bits.
    CCPR1L = DutyCycle >> 2;  //Upper bits.   
}

//Move servor forth and back
void FeedPet (){
    setPWM_DC (DUTY_10);
    SecsDelay (2);
    setPWM_DC (DUTY_5);
    SecsDelay (2);
}

//Steps needed to initialize PWM signal
void PWMInit () {
    TRISIO2 = 1; //Desabling CCP module output. 
    PR2 = Freq50; //PWM 50 Hz freq
    CCP1CONbits.CCP1M = 0b1100; //Selecting PWM mode.
    setPWM_DC (DUTY_5);
    PIR1 &= 0xFD; //clearing timer 2 flag
    T2CON = 0b100; //enabling timer 2 with 0 post and prescaler. 
    while (!(PIR1 & 0x2)); //wait for timer flag to set before activating PWM.
    TRISIO2 = 0; //Enabling CCP output. 
}

void main(void) {
    
    OSCCONbits.IRCF = 0; //Setting 31 kHz clock frequency
    INTCONbits.GIE = 1; //Enabling interrupts
    InitTMR0();
    PWMInit();
    while(1){
        FeedPet();
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
    }
    
}
