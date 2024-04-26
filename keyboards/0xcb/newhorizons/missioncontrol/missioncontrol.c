#include QMK_KEYBOARD_H
#include "print.h"
#include "lib/custom_keycodes.h"
#include "lib/fullscreen_animation.h"
#include "lib/pomodoro.h"
#include "lib/tiny_painter.h"
#include "os_detection.h"

static uint32_t display_sleep_timer;
static uint32_t rgb_sleep_timer;
static uint32_t frame_limit_timer;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        display_sleep_timer = timer_read32();
        rgb_sleep_timer     = timer_read32();
        oled_on();
        rgb_matrix_set_suspend_state(false);
        rgb_matrix_enable_noeeprom();
    }

    return pomodoro_process_record_user(keycode, record);
}

void housekeeping_task_user(void) {
    if (!pomodoro_is_active() && rgb_matrix_is_enabled() && timer_elapsed32(rgb_sleep_timer) > 120000) {
        rgb_matrix_disable_noeeprom();
    }

    pomodoro_tick();
}

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
    pomodoro_render();

    // char result[16] = {0};
    // sprintf(result, "H%d", rgb_matrix_get_hue());
    // oled_set_cursor(0, 0);
    // oled_write(result, false);
    // oled_set_cursor(0, 1);
    // sprintf(result, "S%d", rgb_matrix_get_sat());
    // oled_write(result, false);
    // oled_set_cursor(0, 2);
    // sprintf(result, "V%d", rgb_matrix_get_val());
    // oled_write(result, false);

    return true;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION;
}
