#include "ESP32.h"

bool publishAlert(char alert[]){
  while(!EUSART1_is_tx_ready()){}
  EUSART1_Write(alert);
  return 1;
}
/*
  int size = sizeof alert / sizeof *alert;
  for (int i = 0; i < size; ++i) {
    // do something
  }
 */
bool publishLog(char log[]){
  while(!EUSART1_is_tx_ready()){}
  EUSART1_Write(log);
  return 1;
}