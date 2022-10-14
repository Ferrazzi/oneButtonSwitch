#include <oneButtonSwitch.h>

#define pinButton 10     //OFF pin onebuttonSwitch board
#define pinHoldMOSFET 7  //ON pin onebuttonSwitch board

oneButtonSwitch OBS(pinButton, pinHoldMOSFET, 5000);

void setup() {
}

void loop() {
  OBS.oneButtonSwitchLOOP();
}
