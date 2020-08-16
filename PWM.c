#include <stdint.h>
#include <xc.h>
#include "PWM.h"
#include "timer0.h"

//Change PWM duty cycle
void setPWM_DC (uint8_t DutyCycle){
    TRISIO2 = 1; //Disabling CCP output.
    CCP1CONbits.DC1B = DutyCycle & 3; //lower two bits.
    CCPR1L = DutyCycle >> 2;  //Upper bits.   
    PIR1 &= 0xFD; //clearing timer 2 flag
    while (!(PIR1 & 0x2)); //wait for timer flag to set before activating PWM.
    TRISIO2 = 0; //Enabling CCP output. 
}

//Steps needed to initialize PWM signal
void PWMInit () {
    TRISIO2 = 1; //Desabling CCP module output. 
    PR2 = Freq50; //PWM 50 Hz freq
    CCP1CONbits.CCP1M = 0b1100; //Selecting PWM mode.
    CCP1CONbits.DC1B = DUTY_7 & 3; //lower two bits.
    CCPR1L = DUTY_7 >> 2;  //Upper bits.  
    PIR1 &= 0xFD; //clearing timer 2 flag
    T2CON = 0b100; //enabling timer 2 with 0 post and prescaler. 
    while (!(PIR1 & 0x2)); //wait for timer flag to set before activating PWM.
    TRISIO2 = 0; //Enabling CCP output. 
    SecsDelay (2);
    TRISIO2 = 1; //Desabling CCP module output.
}
