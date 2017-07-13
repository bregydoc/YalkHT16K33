#include "KlayScreen.h"

KlayScreen::KlayScreen(KlayController controller, int mode) {
    this->controller = controller;
    if (mode == MODE_A) {
        this->mode = false;
    }else{
        this->mode = true;
    }
}

void KlayScreen::begin() {
    //controller.begin();
}

void KlayScreen::clearScreen() {
    for (int i=0;i<6;i++) {
        controller.LED_driver1.display_buf[i] = 0;
        controller.LED_driver2.display_buf[i] = 0;
    }
    controller.LED_driver1.write_display();
    controller.LED_driver2.write_display();
}

void KlayScreen::updateScreen() {
    controller.LED_driver1.write_display();
    controller.LED_driver2.write_display();
}

void KlayScreen::setPixel(int x, int y, bool state) {
    //We have 21 cols and 6 rows
    //if x from 0 to 15 (16 cols), use LED_driver1
    //and from 16 to 20 (5 cols more) use LED_driver2
    if (mode) {
        x = 20 - x;
        y = 5 - y;
    }
    if (x<16) {
        //Using LED_driver1
        if (state) {
            controller.LED_driver1.display_buf[y] |= 1<<(x);
        }else{
            controller.LED_driver1.display_buf[y] &= ~1<<(x);
        }
    }else{
        //Using LED_driver2
        if (state) {
            controller.LED_driver2.display_buf[y] |= 1<<(x-16);
        }else{
            controller.LED_driver2.display_buf[y] &= ~1<<(x-16);
        }

    }
}

void KlayScreen::setPixel(int x, int y, uint8_t state) {

    if (mode) {
        x = 20 - x;
        y = 5 - y;
    }

    if (state != 0 && state != 1) {
        return;
    }
    //Using LED_driver1
    if (x<16) {
        if (state==1) {
            controller.LED_driver1.display_buf[y] |= 1<<(x);
        }else{
            controller.LED_driver1.display_buf[y] &= ~1<<(x);
        }
    }else{
        //Using LED_driver2
        if (state==1) {
            controller.LED_driver2.display_buf[y] |= 1<<(x-16);
        }else{
            controller.LED_driver2.display_buf[y] &= ~1<<(x-16);
        }

    }
}

void KlayScreen::draw(uint8_t screen[6][21]) {
    for (int i=0;i<6;i++) {
        for (int j=0;j<21;j++) {
            //setPixel(j, i, screen[i][j]);
            setPixel(j, i, pgm_read_byte( &(screen[i][j]) ));
        }
    }
}

void KlayScreen::fillArea(int x1, int y1, int x2, int y2, uint8_t state) {
    //Basic function for fill any area in the Klay Screen, minified Bres    enham Algorithm
    if (x1>x2) {
        if (y1>y2) {
            for (int i=x2;i<x1+1;i++) {
                for (int j=y2;j<y1+1;j++) {
                    setPixel(i, j, state);
                }
            }
        }else{
            for (int i=x2;i<x1+1;i++) {
                for (int j=y1;j<y2+1;j++) {
                    setPixel(i, j, state);
                }
            }
        }
    }else{
        if (y1>y2) {
            for (int i=x1;i<x2+1;i++) {
                for (int j=y2;j<y1+1;j++) {
                    setPixel(i, j, state);
                }
            }
        }else{
            for (int i=x1;i<x2+1;i++) {
                for (int j=y1;j<y2+1;j++) {
                    setPixel(i, j, state);
                }
            }
        }
    }
}


void KlayScreen::printGoodMessage() {
    draw(goodMessage);

}


void KlayScreen::printCheckMessage(int step) {

    if (step < 31) {
        for (int i=0;i<6;i++) {
            for (int j=0;j<21;j++) {
                setPixel(j, i, pgm_read_byte(&(checkPlease[i][j+step])));
            }
        }
    }

}


void KlayScreen::printNumber(int number, int x, int y) {

    if (number>=0 && number<10) {
        for (int j=x;j<x+4;j++) {
            for (int i=y;i<y+6;i++){
                setPixel(j, i, pgm_read_byte(&(numbers[number][i-y][j-x])));
            }
        }
    }else{
        for (int j=x;j<x+4;j++) {
            for (int i=y;i<y+6;i++){
                setPixel(j, i, pgm_read_byte(&(numbers[10][x][y])));
            }
        }
    }

}
