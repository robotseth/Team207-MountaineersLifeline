/* 
 * File:   display.h
 * Author: Seth Altobelli
 *
 * Created on April 4, 2022, 12:36 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef DISPLAY_H
#define	DISPLAY_H

bool displayActive = 0;

void displayHR(int heartRate);
void displayTemp(int temp);
void displayAlt(int alt);
void displayAltFine(int alt);
void displayOff(void);

#endif	/* DISPLAY_H */


