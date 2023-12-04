#include QMK_KEYBOARD_H
#include "print.h"
#include "lib/fullscreen_animation.h"

static uint32_t display_sleep_timer;
static uint32_t frame_limit_timer;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        display_sleep_timer = timer_read32();
        oled_on();
    }

    return true;
}

// void housekeeping_task_user(void) {
//     // TOOD: Use this to schedule the pomodoro timer changes
// }

bool oled_task_user(void) {
    if (timer_elapsed32(display_sleep_timer) > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    if (frame_limit_timer && timer_elapsed32(frame_limit_timer) < 1000 / 30) {
        return false;
    }

    frame_limit_timer = timer_read32();

    fullscreen_animation();

    return true;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
