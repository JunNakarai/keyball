/*
 * 以下の関数は以下のURLのソースコードを参照または引用しています:
 * https://zenn.dev/takashicompany/articles/69b87160cda4b9
 *
 * 作成者: https://twitter.com/takashicompany
 */

#include QMK_KEYBOARD_H
#include "quantum.h"

enum custom_keycodes {
    KC_MY_BTN1 = KEYBALL_SAFE_RANGE,  //0x5DBB
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_SCR,
    KC_TO_CLICKABLE_INC,              // マウスレイヤーが有効になるまでの待機時間を増やす
    KC_TO_CLICKABLE_DEC,              // マウスレイヤーが有効になるまでの待機時間を減らす
    KC_MY_CMD_X,                      // CMD+X
    KC_MY_CMD_C,                      // CMD+C
    KC_MY_CMD_V,                      // CMD+V
    KC_MY_CMD_Z,                      // CMD+Z
    KC_MY_CMD_SHIFT_Z,                // CMD+SHIFT_Y
};

typedef union {
  uint32_t raw;
  struct {
    // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
    int16_t to_clickable_movement;
  };
} user_config_t;

user_config_t user_config;

// uint16_t to_clickable_time = 50;   // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
int16_t mouse_movement;

extern void enable_click_layer(void) ;
extern void disable_click_layer(void) ;
extern bool process_record_user(uint16_t keycode, keyrecord_t *record);