#include QMK_KEYBOARD_H
#include "lib/custom_keycodes.h"
#include "lib/pomodoro.h"
#include "lib/tiny_painter.h"
#include "print.h"
#include <math.h>

static pomodoro_state_t pomodoro_state = POMODORO_INACTIVE;
static uint32_t         pomodoro_timer = 0;

static int lines = SCREEN_HEIGHT / OLED_FONT_HEIGHT;
static int cols  = SCREEN_WIDTH / OLED_FONT_WIDTH;

static int default_hue = 0;
static int default_sat = 0;
static int default_val = 0;

int get_remaining_time(void) {
    if (pomodoro_state == POMODORO_INACTIVE) {
        return 0;
    }

    uint32_t elapsed = timer_elapsed32(pomodoro_timer);

    if (pomodoro_state == POMODORO_BREAK) {
        if (elapsed > POMODORO_BREAK_TIME) {
            return 0;
        }

        return POMODORO_BREAK_TIME - elapsed;
    }

    if (elapsed > POMODORO_WORK_TIME) {
        return 0;
    }

    return POMODORO_WORK_TIME - elapsed;
}

void set_hue(int h, int s, int v) {
    if (pomodoro_state == POMODORO_INACTIVE) {
        // Store user selected hue
        default_hue = rgb_matrix_get_hue();
        default_sat = rgb_matrix_get_sat();
        default_val = rgb_matrix_get_val();
    }

    rgb_matrix_sethsv_noeeprom(h, s, v);
}

void pomodoro_confirm(void) {
    dprintf("confirm\n");

    set_hue(60, 255, 255);

    pomodoro_state = POMODORO_CONFIRM;
    pomodoro_timer = 0;
}

void pomodoro_start(void) {
    dprintf("start\n");

    set_hue(2, 150, 255);

    pomodoro_state = POMODORO_WORK;
    pomodoro_timer = timer_read32();
}

void pomodoro_start_break(void) {
    dprintf("start\n");

    set_hue(176, 255, 255);

    pomodoro_state = POMODORO_BREAK;
    pomodoro_timer = timer_read32();
}

void pomodoro_stop(void) {
    dprintf("stop\n");

    rgb_matrix_sethsv_noeeprom(default_hue, default_sat, default_val);

    pomodoro_state = POMODORO_INACTIVE;
    pomodoro_timer = 0;
}

void pomodoro_toggle(void) {
    dprintf("toggle\n");

    if (pomodoro_state == POMODORO_INACTIVE) {
        pomodoro_confirm();
    } else {
        pomodoro_stop();
    }
}

void pomodoro_tick(void) {
    if (pomodoro_state == POMODORO_INACTIVE || pomodoro_state == POMODORO_CONFIRM) {
        return;
    }

    uint32_t remaining = get_remaining_time();

    if (pomodoro_state == POMODORO_WORK && remaining == 0) {
        pomodoro_start_break();
    } else if (pomodoro_state == POMODORO_BREAK && remaining == 0) {
        pomodoro_start();
    }
}

void chevron(pixel_state_t frame[SCREEN_WIDTH][SCREEN_HEIGHT], int x, int y) {
    if (x > 0 && x < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT) {
        frame[x][y] = PIXEL_ON;
    }
    if (x + 1 > 0 && x + 1 < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT) {
        frame[x + 1][y] = PIXEL_ON;
    }
    if (x + 2 > 0 && x + 2 < SCREEN_WIDTH && y > 0 && y < SCREEN_HEIGHT) {
        frame[x + 2][y] = PIXEL_OFF;
    }
    if (x > 0 && x < SCREEN_WIDTH && y + 1 > 0 && y + 1 < SCREEN_HEIGHT) {
        frame[x][y + 1] = PIXEL_OFF;
    }
    if (x + 1 > 0 && x + 1 < SCREEN_WIDTH && y + 1 > 0 && y + 1 < SCREEN_HEIGHT) {
        frame[x + 1][y + 1] = PIXEL_ON;
    }
    if (x + 2 > 0 && x + 2 < SCREEN_WIDTH && y + 1 > 0 && y + 1 < SCREEN_HEIGHT) {
        frame[x + 2][y + 1] = PIXEL_ON;
    }
    if (x > 0 && x < SCREEN_WIDTH && y + 2 > 0 && y + 2 < SCREEN_HEIGHT) {
        frame[x][y + 2] = PIXEL_ON;
    }
    if (x + 1 > 0 && x + 1 < SCREEN_WIDTH && y + 2 > 0 && y + 2 < SCREEN_HEIGHT) {
        frame[x + 1][y + 2] = PIXEL_ON;
    }
    if (x + 2 > 0 && x + 2 < SCREEN_WIDTH && y + 2 > 0 && y + 2 < SCREEN_HEIGHT) {
        frame[x + 2][y + 2] = PIXEL_OFF;
    }
}

static int       chevron_pos = 0;
static uint32_t  progress_frame_timer;
static const int pb_width  = SCREEN_WIDTH;
static const int pb_height = OLED_FONT_HEIGHT - 1;
static const int pb_y      = SCREEN_HEIGHT - pb_height;

void render_progress(pixel_state_t frame[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    const double seconds_elapsed = ((double)timer_elapsed32(pomodoro_timer) / 1000);

    if (pomodoro_state == POMODORO_WORK) {
        const double total_seconds = POMODORO_WORK_TIME / 1000;

        for (int i = 0; i < pb_width + 4; i += 4) {
            chevron(frame, -4 + chevron_pos + i, pb_y + 2);
        }

        if (!progress_frame_timer || timer_elapsed32(progress_frame_timer) > (1000 / 4)) {
            chevron_pos++;

            if (chevron_pos > 3) {
                chevron_pos = 0;
            }

            progress_frame_timer = timer_read32();
        }

        double current_bar_width = ((double)pb_width - 4) / total_seconds * seconds_elapsed;
        int    rounded_width     = (int)round(current_bar_width);

        draw_rect(frame, pb_width - 2 - rounded_width, pb_y + 2, rounded_width, pb_height - 4, true, true);

        if (rounded_width > 0) {
            draw_line_to(frame, pb_width - 3 - rounded_width, pb_y + 2, pb_width - 3 - rounded_width, pb_y + pb_height - 3, false);
        }
    } else if (pomodoro_state == POMODORO_BREAK) {
        const double total_seconds     = POMODORO_BREAK_TIME / 1000;
        double       current_bar_width = ((double)pb_width - 4) / total_seconds * seconds_elapsed;
        int          rounded_width     = (int)round(current_bar_width);

        draw_rect(frame, 2, pb_y + 2, pb_width - 4 - rounded_width, pb_height - 4, true, true);
    }

    // Black out 1px border around progress animation
    draw_rect(frame, 1, pb_y + 1, pb_width - 2, pb_height - 2, false, PIXEL_OFF);

    // Draw outside border
    draw_rect_px(frame, 0, pb_y, pb_width, pb_height, false, PIXEL_ON);
}

static char *pad_left(char *str, int width, char padding) {
    int len = strlen(str);
    if (len < width) {
        int spaces = width - len;
        memmove(str + spaces, str, len + 1);
        memset(str, padding, spaces);
    }

    return str;
}

void render_time_remaining(void) {
    uint32_t remaining = get_remaining_time();
    uint32_t minutes   = remaining / (1000 * 60);
    uint32_t seconds   = (remaining / 1000) % 60;
    char     _[]       = " ";
    char     zero[]    = "0";
    char     a_str[16] = {0};

    oled_set_cursor(0, lines - 3);

    if (minutes > 0) {
        sprintf(a_str, "%ld", minutes);
    } else {
        sprintf(a_str, " ");
    }

    oled_write(pad_left(a_str, cols, _[0]), false);

    char b_str[16] = {0};
    sprintf(b_str, "%ld", seconds);
    sprintf(a_str, ":%s", pad_left(b_str, 2, zero[0]));

    oled_set_cursor(0, lines - 2);
    oled_write(pad_left(a_str, cols, _[0]), false);
}

static pixel_state_t frame_buffer[SCREEN_WIDTH][SCREEN_HEIGHT];

void pomodoro_render(void) {
    if (pomodoro_state == POMODORO_INACTIVE) {
        return;
    }

    clear_frame(frame_buffer);
    shift_frame(frame_buffer, 0, 0);

    // Black out background
    if (pomodoro_state == POMODORO_CONFIRM) {
        draw_rect(frame_buffer, 0, SCREEN_HEIGHT - (OLED_FONT_HEIGHT * 4) - 3, pb_width, (OLED_FONT_HEIGHT * 4) + 3, true, PIXEL_OFF);
        render_frame(frame_buffer);
        oled_set_cursor(0, lines - 3);
        oled_write("POMODORO  Y?", false);

        return;
    } else {
        draw_rect(frame_buffer, 0, SCREEN_HEIGHT - (OLED_FONT_HEIGHT * 3) - 3, pb_width, (OLED_FONT_HEIGHT * 3) + 3, true, PIXEL_OFF);
        render_progress(frame_buffer);
        render_frame(frame_buffer);
        render_time_remaining();
    }
}

bool pomodoro_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (pomodoro_state == POMODORO_CONFIRM) {
        if (record->event.pressed) {
            if (keycode == POMODORO_CONFIRM_KEY) {
                pomodoro_start();
            } else {
                pomodoro_stop();
            }
            return false;
        }
    }

    if (record->event.pressed) {
        switch (keycode) {
            case PM_WORK:
                pomodoro_start();
                return false;
            case PM_BRK:
                pomodoro_start_break();
                return false;
            case PM_STOP:
                pomodoro_stop();
                return false;
            case PM_TGGL:
                pomodoro_toggle();
                return false;
                break;
        }
    }

    return true;
}

bool pomodoro_is_active(void) {
    return pomodoro_state != POMODORO_INACTIVE;
}
