#pragma once

#include "quantum.h"

typedef enum { PIXEL_OFF, PIXEL_ON, PIXEL_TRANSPARENT } pixel_state_t;

#ifndef OLED_ROTATION
#    define OLED_ROTATION OLED_ROTATION_270
#endif

#if OLED_ORIENTATION == OLED_ROTATION_0 || OLED_ORIENTATION == OLED_ROTATION_180
#    define SCREEN_WIDTH OLED_DISPLAY_HEIGHT
#    define SCREEN_HEIGHT OLED_DISPLAY_WIDTH
#else
#    define SCREEN_WIDTH OLED_DISPLAY_WIDTH
#    define SCREEN_HEIGHT OLED_DISPLAY_HEIGHT
#endif

// Render methods

void clear_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT]);
void copy_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], pixel_state_t new_frame[SCREEN_WIDTH][SCREEN_HEIGHT], size_t size);
void shift_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], int shift_x, int shift_y);
void render_frame(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT]);

// Draw methods

void draw_line_to(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], int x1, int y1, int x2, int y2, pixel_state_t pixel_state);
void draw_rect(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], uint8_t x, uint8_t y, int width, int height, bool fill, pixel_state_t pixel_state);
void draw_rect_px(pixel_state_t screen[SCREEN_WIDTH][SCREEN_HEIGHT], uint8_t x, uint8_t y, int width, int height, bool fill, pixel_state_t pixel_state);
