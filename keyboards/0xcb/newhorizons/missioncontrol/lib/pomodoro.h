#pragma once

#include QMK_KEYBOARD_H
#include "pomodoro.h"
#include "tiny_painter.h"

#ifndef POMODORO_WORK_TIME
#    define POMODORO_WORK_TIME 15 * 60 * 1000
#endif

#ifndef POMODORO_BREAK_TIME
#    define POMODORO_BREAK_TIME 5 * 60 * 1000
#endif

#ifndef POMODORO_CONFIRM_KEY
#    define POMODORO_CONFIRM_KEY KC_ENT
#endif

// Pomodoro

typedef enum { POMODORO_INACTIVE, POMODORO_CONFIRM, POMODORO_WORK, POMODORO_BREAK } pomodoro_state_t;

void pomodoro_tick(void);
void pomodoro_render(void);
bool pomodoro_process_record_user(uint16_t keycode, keyrecord_t* record);
bool pomodoro_is_active(void);
