/* 
 * File:   GPIOs.h
 * Author: uriel
 *
 * Created on June 17, 2020, 12:35 PM
 */

#ifndef GPIOS_H
#define	GPIOS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>

#define GP4Mask 0x8
    
void initGPIOs (void);
void initGP3 (void);
void initLEDs (void);
void turnOnOne (void);
void turnOnTwo (void);
void turnOnThree (void);
void turnOffLEDs (void);
#ifdef	__cplusplus
}
#endif

#endif	/* GPIOS_H */

