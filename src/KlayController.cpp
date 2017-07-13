#include "KlayController.h"
#include <Wire.h>


KlayController::KlayController(): LED_driver1(0x70), LED_driver2(0x71) {

}

void KlayController::begin() {
    Wire.begin();
    LED_driver1.begin();
    LED_driver2.begin();
}
