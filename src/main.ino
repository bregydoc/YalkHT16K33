#include <Arduino.h>
#include "KlayScreen.h"
#include "KlayKeyboard.h"
#include <avr/pgmspace.h>

#define DEBUG_MODE
#define BUILTIN_DEBUG


KlayController mainController;

KlayScreen screen(mainController, MODE_B);
KlayKeyboard keyboard(mainController);

//////////////////////////////////////////////////////////////////
// Por limitaciones hardware se cambio el máximo número de 39 a 29
//////////////////////////////////////////////////////////////////
int initNumber;

void view1 (int* NUM);
void view2 (int* NUM);
void view3 (int* NUM);
void view4 (int* NUM);


void setup() {
    mainController.begin();

    screen.clearScreen();
    screen.updateScreen();
    #ifdef DEBUG_MODE
    Serial.begin(115200);
    #endif



}

void loop() {
    keyboard.updateKeys();
    int number = keyboard.getNumberCodeFromKeyboardA();
    //initNumber = 10;
    #ifdef DEBUG_MODE
    Serial.println(number);
    #endif
    switch (number) {
        case 1:
            view1(&initNumber);
            #ifdef DEBUG_MODE
            Serial.println(initNumber);
            #endif
            while (keyboard.getNumberCodeFromKeyboardA()!=2) {
                keyboard.updateKeys();
            }
            break;
        case 2:
            view2(&initNumber);
            #ifdef DEBUG_MODE
            Serial.println(initNumber);
            #endif
            while (keyboard.getNumberCodeFromKeyboardA()!=3) {
                keyboard.updateKeys();
            }
            break;
        case 3:
            view3(&initNumber);
            #ifdef DEBUG_MODE
            Serial.println(initNumber);
            #endif
            while (keyboard.getNumberCodeFromKeyboardA()!=4) {
                keyboard.updateKeys();
            }

            break;
        case 4:
            view4(&initNumber);
            #ifdef DEBUG_MODE
            Serial.println(initNumber);
            #endif
            while (keyboard.getNumberCodeFromKeyboardA()!=0) {
                keyboard.updateKeys();
            }
            break;
        default:
            break;
    }


}


void view1(int* NUM) {

    screen.clearScreen();
    screen.updateScreen();

    int finishedPad = 0; //pad "A10", in the matrix is the (9,0) coordinate
    #ifdef DEBUG_MODE
    int m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View1, branch1");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        finishedPad = keyboard.keyboardB[9][0];//(9,0) coordinate
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (finishedPad==0);

    keyboard.updateKeys();

    //get area from (1,0) to (7,5)
    //*NUM = keyboard.getActiveKeysInArea(1, 0, 6, 5); //For 29 pads (30)

    //Toda la fila f no funciona, por eso se utiliza la fila anterior (f10 -> e10)
    //Tambien se modifica el area de captura

    *NUM = keyboard.getActiveKeysInArea(0, 1, 7, 5); //MOD: 39 pads

    int nextViewPad = 0; //Pad e10
    #ifdef DEBUG_MODE
    m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View1, branch2");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        nextViewPad = keyboard.keyboardB[9][4];//(9,4) coordinate Pad e10
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (nextViewPad==0);

}

void view2 (int* NUM) {
    //Example is number 15:
    int tensExpected = (*NUM/10) * 10;// Example 15/10 -> 1 * 10 -> (10);
    int unitsExpected = *NUM - tensExpected;//Example 15 - 10 -> (5);

    #ifdef DEBUG_MODE
    Serial.print("Tens expected: ");Serial.print(tensExpected); Serial.print(", Units expected: "); Serial.println(unitsExpected);
    #endif

    int tensNum = 0;
    int unitsNum = 0;

    int stepAux = 0;

    while(tensNum != tensExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View2, branch1");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        tensNum = keyboard.getActiveKeysInArea(0, 0, 4, 5); // Area for Tens
        //tensNum = keyboard.getActiveKeysInArea(1, 0, 4, 5);
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
    }

    screen.printGoodMessage();
    screen.updateScreen();

    delay(3000);

    screen.clearScreen();
    screen.updateScreen();

    while(unitsNum != unitsExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View2, branch2");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        unitsNum = keyboard.getActiveKeysInArea(6, 1, 8, 3); // Area for units
        //unitsNum = keyboard.getActiveKeysInArea(6, 1, 8, 3);
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
    }

    //Blink "BIEN" message:
    for (int repeat=0;repeat<8;repeat++) {
        #ifdef DEBUG_MODE
        Serial.println("View2, branch3");
        #endif
        screen.clearScreen();
        screen.updateScreen();
        delay(100);
        screen.printGoodMessage();
        screen.updateScreen();
        delay(500);
    }


    int finishedPad = 0; //pad "A10", in the matrix is the (9,0) coordinate
    #ifdef DEBUG_MODE
    int m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View2, branch4");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        finishedPad = keyboard.keyboardB[9][0];//(9,0) coordinate
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (finishedPad==0);

    keyboard.updateKeys();

    int nextViewPad = 0; //Pad e10
    #ifdef DEBUG_MODE
    m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View2, branch3");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        nextViewPad = keyboard.keyboardB[9][4];//(9,4) coordinate Pad e10
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (nextViewPad==0);

}

void view3(int* NUM) {
    //Example is number 15:
    int tensExpected = (*NUM/10);// Example 15/10 -> (1);
    int unitsExpected = *NUM - (tensExpected * 10);//Example 15 - (1 * 10) -> (5);

    #ifdef DEBUG_MODE
    Serial.print("Tens expected: ");Serial.print(tensExpected); Serial.print(", Units expected: "); Serial.println(unitsExpected);
    #endif

    int tensNum = -1;
    int unitsNum = -1;

    int stepAux = 0;

    while(tensNum != tensExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View3, branch1");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        Serial.println(tensNum);
        #endif
        keyboard.updateKeys();
        // Getting tens from 6 pads area, the number is a Klay code
        tensNum = keyboard.getDigitCodeFromArea(0, 1, 2, 2); //Area for tens digit
        //tensNum = keyboard.getDigitCodeFromArea(1, 0, 3, 1);
        /////////////////////////////////////////
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
    }

    screen.printGoodMessage();
    screen.updateScreen();

    delay(3000);

    screen.clearScreen();
    screen.updateScreen();

    while(unitsNum != unitsExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View3, branch2");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        Serial.println(unitsNum);
        #endif
        keyboard.updateKeys();
        //Method like get tens
        unitsNum = keyboard.getDigitCodeFromArea(4, 1, 6, 2); //units digit
        //unitsNum = keyboard.getDigitCodeFromArea(5, 0, 7, 1);
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
    }

    //Blink "BIEN" message:
    for (int repeat=0;repeat<8;repeat++) {
        #ifdef DEBUG_MODE
        Serial.println("View3, branch3");
        #endif
        screen.clearScreen();
        screen.updateScreen();
        delay(100);
        screen.printGoodMessage();
        screen.updateScreen();
        delay(500);
    }

    int finishedPad = 0; //pad "A10", in the matrix is the (9,0) coordinate
    #ifdef DEBUG_MODE
    int m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View3, branch4");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        finishedPad = keyboard.keyboardB[9][0];//(9,0) coordinate
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (finishedPad==0);


    keyboard.updateKeys();


    int nextViewPad = 0; //Pad e10
    #ifdef DEBUG_MODE
    m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View3, branch3");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        nextViewPad = keyboard.keyboardB[9][4];//(9,4) coordinate Pad e10
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (nextViewPad==0);

}

void view4 (int* NUM) {
    screen.clearScreen();
    screen.updateScreen();
    //Example is number 15:
    int tensExpected = (*NUM/10);// Example 15/10 -> (1);
    int unitsExpected = *NUM - (tensExpected * 10);//Example 15 - (1 * 10) -> (5);

    #ifdef DEBUG_MODE
    Serial.print("Tens expected: ");Serial.print(tensExpected); Serial.print(", Units expected: "); Serial.println(unitsExpected);
    #endif

    int tensNum = -1;
    int unitsNum = -1;

    int stepAux = 0;

    while(tensNum != tensExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View4, branch1");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        Serial.println(tensNum);
        #endif
        keyboard.updateKeys();
        // Getting tens from 6 pads area, the number is a Klay code
        tensNum = keyboard.getDigitCodeFromArea(0, 1, 2, 2); //Area for tens digit
        /////////////////////////////////////////
        /*
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
        */
        //screen.setPixel(18, 5,(uint8_t) 1);
        screen.printNumber(tensNum, 11, 0);
        //screen.printNumber(unitsNum, 16, 0);
        screen.updateScreen();
    }
    delay(2000);

    screen.clearScreen();

    screen.printGoodMessage();
    screen.updateScreen();

    delay(3000);

    screen.clearScreen();
    screen.updateScreen();

    while(unitsNum != unitsExpected) {
        #ifdef DEBUG_MODE
        if (stepAux%100) {
            Serial.println("View4, branch2");
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(20);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        Serial.println(unitsNum);
        #endif
        keyboard.updateKeys();
        //Method like get tens
        unitsNum = keyboard.getDigitCodeFromArea(4, 1, 6, 2);
        /*
        screen.printCheckMessage(stepAux/10);
        screen.updateScreen();
        stepAux++;
        if (stepAux > 310) {
            stepAux = 0;
        }
        */

        //screen.setPixel(18, 5,(uint8_t) 1);
        screen.printNumber(tensNum, 11, 0);
        screen.printNumber(unitsNum, 16, 0);
        screen.updateScreen();
    }
    delay(2000);
    screen.clearScreen();
    screen.updateScreen();
    //Blink "BIEN" message:
    for (int repeat=0;repeat<8;repeat++) {
        #ifdef DEBUG_MODE
        Serial.println("View4, branch3");
        #endif
        screen.clearScreen();
        screen.updateScreen();
        delay(100);
        screen.printGoodMessage();
        screen.updateScreen();
        delay(500);
    }

    int finishedPad = 0; //pad "A10", in the matrix is the (9,0) coordinate
    #ifdef DEBUG_MODE
    int m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View4, branch4");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        finishedPad = keyboard.keyboardB[9][0];//(9,0) coordinate
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (finishedPad==0);


    keyboard.updateKeys();


    int nextViewPad = 0; //Pad e10
    #ifdef DEBUG_MODE
    m=0;
    #endif
    do {
        #ifdef DEBUG_MODE
        if (m%500) {
            Serial.println("View4, branch3");
            m=0;
            #ifdef BUILTIN_DEBUG
            screen.setPixel(20, 5,(uint8_t) 1);
            screen.updateScreen();
            delay(50);
            screen.setPixel(20, 5,(uint8_t) 0);
            screen.updateScreen();
            #endif
        }
        #endif
        keyboard.updateKeys();
        nextViewPad = keyboard.keyboardB[9][4];//(9,4) coordinate Pad e10
        delay(10);
        #ifdef DEBUG_MODE
        m++;
        #endif
    } while (nextViewPad==0);
}
