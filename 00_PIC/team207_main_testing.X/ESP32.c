#include "ESP32.h"

bool publishAlert(char alert[]){
  while(!EUSART2_is_tx_ready()){}
  EUSART2_Write((uint8_t) alert);
  return 1;
}
/*
  int size = sizeof alert / sizeof *alert;
  for (int i = 0; i < size; ++i) {
    // do something
  }
 */
bool publishLog(char log[]){
  while(!EUSART2_is_tx_ready()){}
  EUSART2_Write((uint8_t) log);
  return 1;
}