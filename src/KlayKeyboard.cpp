#include "KlayKeyboard.h"

KlayKeyboard::KlayKeyboard(KlayController controller) {
    this->controller = controller;
}

void KlayKeyboard::updateKeys() {
    
    controller.LED_driver1.read_key_memory();
    controller.LED_driver2.read_key_memory();
    
    for (int i = 0; i < 3; i++) {
        keys_buf1[i] = controller.LED_driver1.keys_buf[i];
        keys_buf2[i] = controller.LED_driver2.keys_buf[i];
    }

    for (int y=0; y<3; y++) {
        for (int x=0; x<3; x++) {
            //Working but is a slowly method
            int v = bitRead(keys_buf1[y], x);
            keyboardA[2-x][y] = v;
        }   
    }

    for (int y=0; y<3; y++) {
        for (int x=0; x<10; x++) {
            int v = bitRead(keys_buf1[y], x+3);//From bit3 to bit12 [10 pads]
            keyboardB[9-x][y] = v;
        }
    }

    for (int y=0; y<3; y++) {
        for (int x=0; x<10; x++) {
            int v = bitRead(keys_buf2[y], x);//From bit0 to bit9 [10 pads]
            keyboardB[9-x][y+3] = v;
        }
    }

    //keyboardA

}
int KlayKeyboard::getActiveKeysInKeyboardA() {
    int m = 0;
    for (int y=0; y<3; y++) {
        for (int x=0; x<3; x++) {
            m = keyboardA[x][y]==1?m+1:m;
        }
    }
    return m;
}

int KlayKeyboard::getActiveKeysInKeyboardB() {
    int m = 0;
    for (int y=0; y<6; y++) {
        for (int x=0; x<10; x++) {
            m = keyboardB[x][y]==1?m+1:m;
        }
    }
    return m;
}

//Only case when y2 and x2 are bigger than x1 and y1
int KlayKeyboard::getActiveKeysInArea(int x1, int y1, int x2, int y2) {
    int m = 0;
    for (int y=y1; y<y2+1; y++) {
        for (int x=x1; x<x2+1; x++) {
            m = keyboardB[x][y]==1?m+1:m;
        }
    }
    return m;
}

/*
int KlayKeyboard::getNumberCodeFromKeyboardA() {
    return keyboardA[0][0] + keyboardA[1][0]*2 + keyboardA[2][0]*4;
}
*/
int KlayKeyboard::getNumberCodeFromKeyboardA() {
    return keyboardA[1][0] + keyboardA[2][0]*2 + keyboardA[1][1]*4;
}
int KlayKeyboard::pow(int x, int y) {
    int m = 1;
    if (y==0) {
        return m;
    }
    for (int i=0;i<y;i++) {
        m *= x;
    }

    return m;
}

int KlayKeyboard::getDigitCodeFromArea(int x1, int y1, int x2, int y2) {
    //M is binary codec number
    int m = 0;
    int aux = 0;
    for (int y=y1; y<y2+1; y++) {
        for (int x=x1; x<x2+1; x++) {
            m += keyboardB[x][y]==1?pow(2, aux):0;
            aux++;
        }
    }
    switch (m) {
        case 0: //Nothing card
            return -1;
        case 1:
            return 0;
        case 2:
            return 1;
        case 10:
            return 2;
        case 4:
            return 3;
        case 3:
            return 4;
        case 6:
            return 5;
        case 8:
            return 6;
        case 9:
            return 7;
        case 11:
            return 8;
        case 7:
            return 9;
    }
    return -1;
}
