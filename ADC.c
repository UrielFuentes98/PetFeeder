#include <stdint.h>
#include <xc.h>
#include "ADC.h"
#include "GPIOs.h"

void initADC0(void){
    //Setting GP0 as analog input
    TRISIO0 = 1;
    ANS0 = 1;
    ADCON0bits.CHS = 0; //Selecting channel 0
    ADCON0bits.VCFG = 0; //Vdd as reference
    ANSELbits.ADCS = 0; //Conversion freq = clk / 2
    ADCON0bits.ADFM = 1; //Right adjusted result
    ADCON0bits.ADON = 1; //Enable conversion    
}

frequencies getFreq (void){
    frequencies retFreq;
    uint8_t ADCread;
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO);
    ADCread = ADRESH & 3;
    switch (ADCread){
        case 2: 
            retFreq = TWICE_D;
            turnOnTwo();
            break;
        case 3:
            retFreq = THREE_D;
            turnOnThree();
            break;
        default:
            retFreq = ONCE_D;
            turnOnOne();
    }
    return retFreq;
}
