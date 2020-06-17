/* 
 * File:   PWM.h
 * Author: uriel
 *
 * Created on June 16, 2020, 6:14 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>

#define DUTY_2 13
#define DUTY_3 19
#define DUTY_4 25
#define DUTY_5 31 // 5% - 31 
#define DUTY_6 36
#define DUTY_7 42
#define DUTY_8 48
#define DUTY_9 52
#define DUTY_10 60 //10% - 60
#define DUTY_11 66
#define DUTY_12 72
#define DUTY_14 84
#define Freq50 142 //with formula should 154, but after calibration 142
    
void setPWM_DC (uint8_t DutyCycle);
void PWMInit (void);


#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

