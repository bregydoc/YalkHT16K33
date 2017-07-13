#include <stdint.h>
#include <Wire.h>
#include <Arduino.h>
#include "HT16K33.h"


HT16K33::HT16K33(uint8_t addr){
    i2c_addr = addr;
}

void HT16K33::begin(void){
    HT16K33::send_single_cmd(HT_CMD_SYSTEM_SETUP  | 0x01);
    HT16K33::send_single_cmd(HT_CMD_DISPLAY_SETUP | 0x01);
    HT16K33::send_single_cmd(HT_CMD_DIMMING_SET   | 0x02);
}

void HT16K33::send_single_cmd(uint8_t cmd){
    Wire.beginTransmission(i2c_addr);
    Wire.write(cmd);
    Wire.endTransmission();

}

void HT16K33::send_cmd(uint8_t cmd, uint8_t data){
    Wire.beginTransmission(i2c_addr);
    Wire.write(cmd);
    Wire.write(data);
    Wire.endTransmission();
}

void HT16K33::write_display(void){

    Wire.beginTransmission(i2c_addr);
    Wire.write((uint8_t)0x00);                     // start at address $00

    for (uint8_t i=0; i<8; i++){
        Wire.write(display_buf[i] & 0xFF);
        Wire.write(display_buf[i] >> 8);
    }
    Wire.endTransmission();
}

void HT16K33::read_key_memory(void){

    memset(keys_buf, 0x00, sizeof(keys_buf));
    delay(30);

    Wire.beginTransmission(i2c_addr);
    Wire.write((uint8_t)0x40);                      // start at address $40H
    Wire.endTransmission();

    Wire.requestFrom(i2c_addr, 6);

    int i = 0;
    while(Wire.available()){

        keys_buf[i]   =  Wire.read();
        keys_buf[i]  += (Wire.read() << 8);
        i++;
    }
}
