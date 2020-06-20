/* 
 * File:   ADC.h
 * Author: uriel
 *
 * Created on June 19, 2020, 5:22 PM
 */

#ifndef ADC_H
#define	ADC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <xc.h>
typedef enum {ONCE_D, TWICE_D, THREE_D} frequencies;

void initADC0(void);
frequencies getFreq (void);

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

