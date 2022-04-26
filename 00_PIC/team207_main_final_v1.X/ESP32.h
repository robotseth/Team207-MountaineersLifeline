/* 
 * File:   ESP32.h
 * Author: Seth Altobelli
 *
 * Created on April 4, 2022, 12:23 PM
 */
#include "mcc_generated_files/mcc.h"

#ifndef ESP32_H
#define	ESP32_H

bool publishAlert(char alert[]);
bool publishLog(char log[]);

#endif	/* ESP32_H */

