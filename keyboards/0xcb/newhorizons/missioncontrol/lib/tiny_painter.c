#include "quantum.h"
#include "tiny_painter.h"

/*
Tiny Painter draws small things on tiny OLED screens.

It's a tiny collection of functions which modify a 2D array of pixel states plus
a convenience function to render the array to the OLED screen using QMK's oled_write_pixel()

QMK has it's Painter API, but what's the fun in that? This is a fun little exercise.
It might even work on non-RP2040 boards. I haven't tested it though.

– @pichfl
*/

// Draw methods

void draw_line_to(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], int x1, int y1, int x2, int y2, pixel_state_t pixel_state) {
    if (x1 == x2) {
        for (uint8_t i = y1; i <= y2; i++) {
            screen[x1][i] = pixel_state;
        }
        return;
    } else if (y1 == y2) {
        for (uint8_t i = x1; i <= x2; i++) {
            screen[i][y1] = pixel_state;
        }
        return;
    }

    // Ignore diagonal lines for now
    // int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    // int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    // int err = dx + dy, e2;

    // while (true) {
    //     screen[x1][y1] = pixel_state;
    //     if (x1 == x2 && y1 == y2) break;
    //     e2 = 2 * err;
    //     if (e2 >= dy) {
    //         err += dy;
    //         x1 += sx;
    //     }
    //     if (e2 <= dx) {
    //         err += dx;
    //         y1 += sy;
    //     }
    // }
}

void draw_rect(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], uint8_t x, uint8_t y, int width, int height, bool fill, pixel_state_t pixel_state) {
    uint8_t x2 = x + width - 1;
    uint8_t y2 = y + height - 1;

    if (fill) {
        for (uint8_t i = y; i <= y2; i++) {
            draw_line_to(screen, x, i, x2, i, pixel_state);
        }
    } else {
        draw_line_to(screen, x, y, x2, y, pixel_state);
        draw_line_to(screen, x, y2, x2, y2, pixel_state);
        draw_line_to(screen, x, y, x, y2, pixel_state);
        draw_line_to(screen, x2, y, x2, y2, pixel_state);
    }
}

void draw_rect_px(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], uint8_t x, uint8_t y, int width, int height, bool fill, pixel_state_t pixel_state) {
    uint8_t x2 = x + width - 1;
    uint8_t y2 = y + height - 1;

    if (fill) {
        draw_line_to(screen, x + 1, y, x2 - 1, y, pixel_state);

        for (uint8_t i = y + 1; i <= y2 - 1; i++) {
            draw_line_to(screen, x, i, x2, i, pixel_state);
        }

        draw_line_to(screen, x + 1, y2, x2 - 1, y2, pixel_state);
    } else {
        draw_line_to(screen, x + 1, y, x2 - 1, y, pixel_state);   // top
        draw_line_to(screen, x + 1, y2, x2 - 1, y2, pixel_state); // bottom
        draw_line_to(screen, x, y + 1, x, y2 - 1, pixel_state);   // left
        draw_line_to(screen, x2, y + 1, x2, y2 - 1, pixel_state); // right
    }
}

void clear_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            screen[x][y] = PIXEL_TRANSPARENT;
        }
    }
}

void copy_frame(pixel_state_t (*frame)[SCREEN_HEIGHT], pixel_state_t (*new_frame)[SCREEN_HEIGHT], size_t size) {
    memcpy(frame, new_frame, size);
}

void shift_frame(pixel_state_t frame[SCREEN_WIDTH][SCREEN_HEIGHT], int shift_x, int shift_y) {
    if (shift_x == 0 && shift_y == 0) {
        return;
    }

    pixel_state_t new_frame[SCREEN_WIDTH][SCREEN_HEIGHT] = {{PIXEL_TRANSPARENT}};

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            int new_x = x + shift_x;
            int new_y = y + shift_y;

            if (new_x >= 0 && new_x < SCREEN_WIDTH && new_y >= 0 && new_y < SCREEN_HEIGHT) {
                new_frame[new_x][new_y] = frame[x][y];
            }
        }
    }

    copy_frame(frame, new_frame, sizeof(new_frame));
}

void render_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT]) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            if (screen[x][y] == PIXEL_ON) {
                oled_write_pixel(x, y, true);
            } else if (screen[x][y] == PIXEL_OFF) {
                oled_write_pixel(x, y, false);
            }
        }
    }
}
