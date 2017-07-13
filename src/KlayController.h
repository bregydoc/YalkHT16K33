#ifndef KlayController_h
#define KlayController_h
#include <Arduino.h>
#include "HT16K33.h"

class KlayController {

private:

public:
    //HT16K33_ADDR1 = 0x70
    //HT16K33_ADDR2 = 0x71
    HT16K33 LED_driver1;
    HT16K33 LED_driver2;
    KlayController();
    void begin();

};

#endif
