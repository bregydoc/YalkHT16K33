#ifndef HT16K33_H
#define HT16K33_H
#include <Arduino.h>


/* Macros used for HT16K33 commands */
#define HT_DISPLAY_DATA          0x00
#define HT_CMD_SYSTEM_SETUP      0x20
#define HT_KEY_DATA              0x40
#define HT_CMD_INT_FLAG_ADDR     0x60
#define HT_CMD_DISPLAY_SETUP     0x80
#define HT_CMD_INT_SET           0xA0
#define HT_CMD_DIMMING_SET       0xE0


class HT16K33{

private:

public:
    uint16_t display_buf[8];
    uint16_t keys_buf[3];
    uint8_t  i2c_addr;

    HT16K33(uint8_t addr);
    void begin();
    void send_single_cmd(uint8_t cmd);
    void send_cmd(uint8_t cmd, uint8_t data);
    void write_display();
    void read_key_memory();
};

#endif
