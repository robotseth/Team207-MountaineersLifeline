#include "timers.h"

uint16_t millis(){
    currentTime = TMR0_ReadTimer(void * scale);
    return currentTime;
}