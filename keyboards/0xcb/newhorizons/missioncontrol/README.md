# New Horizons: Mission Control

Modifications made by @pichfl.

The original new Horizons is a genius board. It's pretty, it's versatile, it's slightly different.
I fell in love with it, but while I do enjoy my microcontrollers, looking at their backside, even
a pretty one, is not what I had in mind. The Helios controller had plenty of pins to spare, so
I did what every tinkerer would do and added a tiny display.

It's mostly decoration, but since I wanted to try the Pomodoro technique, I added a timer, too.

## Features

-   [x] OLED Display with hand-drawn animation of the New Horizons probe floating near Pluto
-   [x] Pomodoro timer
    -   [x] Work and break intervals displayed on screen
    -   [ ] Add under-glow hue changes to indicate the current interval
-   [ ] Custom fade-out animation for the OLED display

## Pomodoro Timer

The timer only supports work and short break intervals. It will switch between them automatically.
For longer breaks just stop the timer and start it again when you're ready.

## Configuration

You can use the following keycodes in your `keymap.c` to control the timer:

| Keycode    | Description                                           |
| ---------- | ----------------------------------------------------- |
| `PM_TGGLE` | Waits for confirmation to start the timer or stops it |
| `PM_WORK`  | Starts the work timer without confirmation            |
| `PM_BRK`   | Starts the break timer without confirmation           |
| `PM_STOP`  | Stops the timer                                       |

You can add the following lines to your `config.h` to configure the timer:

| Option                 | Description                       | Default                                  |
| ---------------------- | --------------------------------- | ---------------------------------------- |
| `POMODORO_WORK_TIME`   | Time in ms for the work interval  | `25 * 60 * 1000` (25min)                 |
| `POMODORO_BREAK_TIME`  | Time in ms for the break interval | `5 * 60 * 1000` (5min)                   |
| `POMODORO_CONFIRM_KEY` | Keycode to confirm the timer      | `KC_ENTER`                               |
| `OLED_ROTATION`        | Rotation of the OLED display      | `OLED_ROTATION_270` (pins pointing down) |

## Requirements

-   [0xCB Helios](https://keeb.supply/products/0xcb-helios) or any other RP2040 based board with 2 spare pins
-   128x32px SSD1306 OLED Panel (I2C) from a shop of your choice

## Compiling the firmware

```bash
qmk compile -kb 0xcb/newhorizons/missioncontrol -km pichfl
```
