/*
 * 以下の関数は以下のURLのソースコードを参照または引用しています:
 * https://zenn.dev/takashicompany/articles/69b87160cda4b9
 *
 * 作成者: https://twitter.com/takashicompany
 */

#include "quantum.h"

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
int16_t mouse_movement;

typedef union {
  uint32_t raw;
  struct {
    // int16_t to_clickable_time; // // この秒数(千分の一秒)、WAITING状態ならクリックレイヤーが有効になる。  For this number of seconds (milliseconds), if in WAITING state, the click layer is activated.
    int16_t to_clickable_movement;
  };
} user_config_t;

user_config_t user_config;

enum custom_keycodes {
    KC_MY_BTN1 = KEYBALL_SAFE_RANGE,
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_SCR,
    KC_TO_CLICKABLE_INC,
    KC_TO_CLICKABLE_DEC
};

enum click_state {
    NONE = 0,
    WAITING,    // マウスレイヤーが有効になるのを待つ。 Wait for mouse layer to activate.
    CLICKABLE,  // マウスレイヤー有効になりクリック入力が取れる。 Mouse layer is enabled to take click input.
    CLICKING,   // クリック中。 Clicking.
    SCROLLING   // スクロール中。 Scrolling.
};

enum click_state state;                   // 現在のクリック入力受付の状態 Current click input reception status
void eeconfig_init_user(void);
void keyboard_post_init_user(void);       // クリック用のレイヤーを有効にする。　Enable layers for clicks
void enable_click_layer(void);            // クリック用のレイヤーを無効にする。 Disable layers for clicks.
void disable_click_layer(void);           // 自前の絶対数を返す関数。 Functions that return absolute numbers.
int16_t my_abs(int16_t num);              // 自前の符号を返す関数。 Function to return the sign.
int16_t mmouse_move_y_sign(int16_t num);  // 現在クリックが可能な状態か。 Is it currently clickable?
bool is_clickable_mode(void);
bool process_record_user(uint16_t keycode, keyrecord_t *record);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);