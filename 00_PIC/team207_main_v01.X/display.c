#include "display.h"
#include "timers.h"

void displayHR(int heartRate)
{
    // turn on blue LED
    // pulse (other?) LED at heart rate
}

void displayTemp(int temp)
{
    // set LED color based on temp
}

void displayAlt(int alt)
{
    displayActive = 1;
    // turn off LED
    float rate = alt * 0.00161290322;
    int delay_ms = (int)(1/rate);
    unsigned long time = 0;
    if (millis() - time >= delay_ms && displayActive == 1){
        // toggle LED
        time = millis();
    }
}

void displayAltFine(int alt)
{
    // turn on blue LED
    // pulse (other?) LED for altitude
}

void displayOff(void)
{
    // turn off LED
    displayActive = 0;
}
