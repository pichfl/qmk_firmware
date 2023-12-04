# New Horizons: Mission Control

Modifications made by @pichfl

## Features

- OLED Display with hand drawn animation of the New Horizons probe floating near Pluto

## Requirements

- [0xCB Helios](https://keeb.supply/products/0xcb-helios) or any other RP2040 based board with 2 spare pins
- 128x32px SSD1306 OLED Panel (I2C) from a shop of your choice

## Compiling the firmware

```bash
qmk compile -kb 0xcb/newhorizons/missioncontrol -km pichfl
```
