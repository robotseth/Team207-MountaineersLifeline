#include "timers.h"

long millis(){
    long returnTime = 0;
    returnTime = (long) TMR1_ReadTimer()*scale;
    return returnTime;
}
