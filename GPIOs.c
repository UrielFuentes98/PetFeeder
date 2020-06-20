#include <stdint.h>
#include <xc.h>
#include "GPIOs.h"

void initGPIOs (void) {
    OPTION_REGbits.nGPPU = 0;
    initGP3();
    initLEDs();
}

void initLEDs (void){
    TRISIO1 = 0; //GP1 as output
    TRISIO4 = 0; //GP4 as output
    TRISIO5 = 0; //GP5 as output
}

void turnOnOne (void){
    GP5 = 1;
    GP4 = 0;
    GP1 = 0;
}

void turnOnTwo (void){
    GP5 = 1;
    GP4 = 1;
    GP1 = 0;
}
void turnOnThree (void){
    GP5 = 1;
    GP4 = 1;
    GP1 = 1;   
}

void turnOffLEDs (void){
    GP5 = 0;
    GP4 = 0;
    GP1 = 0;    
}

void initGP3 (void) {
    TRISIO3 = 1; //GP0 set as input
    IOC3 = 1; //Interrupt on change enabled   
}