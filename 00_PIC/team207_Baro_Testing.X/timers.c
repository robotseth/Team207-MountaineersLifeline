#include "timers.h"

uint16_t millis(){
    currentTime = TMR0_ReadTimer()*scale;
    return currentTime;
}
