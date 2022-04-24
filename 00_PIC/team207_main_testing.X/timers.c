#include "timers.h"

unsigned long millis(){
    unsigned long returnTime = 0;
    returnTime = (unsigned long) TMR1_ReadTimer()*scale;
    return returnTime;
}
