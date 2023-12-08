#pragma once

#include QMK_KEYBOARD_H

enum pomodoro_keycodes {
    PM_WORK = SAFE_RANGE, // Start working
    PM_BRK,               // Start break
    PM_STOP,              // Stop
    PM_TGGL,              // Toggle
};
