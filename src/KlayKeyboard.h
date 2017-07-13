#ifndef KlayKeyboard_h
#define KlayKeyboard_h

#include <Arduino.h>
#include "HT16K33.h"
#include "KlayController.h"

class KlayKeyboard {

private:
    KlayController controller;

    int pow(int x, int y);
public:

    uint16_t keys_buf1[3];
    uint16_t keys_buf2[3];

    int keyboardA[3][3];
    bool keyboardB[10][6];

    //HT16K33_ADDR1 = 0x70
    //HT16K33_ADDR2 = 0x71
    KlayKeyboard(KlayController controller);
    void begin();
    //First layer
    void updateKeys();
    //Second layer
    int getActiveKeysInKeyboardA();
    int getActiveKeysInKeyboardB();

    int getActiveKeysInArea(int x1, int y1, int x2, int y2);
    int getNumberCodeFromKeyboardA();
    int getDigitCodeFromArea(int x1, int y1, int x2, int y2);

};



#endif
