#include "timers.h"

uint16_t millis(){
    currentTime = TMR0_ReadTimer();
    return currentTime*SCALEFCTR;
}
