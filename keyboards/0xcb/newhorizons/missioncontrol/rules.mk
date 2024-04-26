ENCODER_MAP_ENABLE = yes
CONSOLE_ENABLE = yes
AUDIO_DRIVER = pwm_hardware
OS_DETECTION_ENABLE = yes
RGB_DISABLE_WHEN_USB_SUSPENDED = yes

SRC += keyboards/0xcb/newhorizons/missioncontrol/lib/fullscreen_animation.c \
       keyboards/0xcb/newhorizons/missioncontrol/lib/tiny_painter.c \
       keyboards/0xcb/newhorizons/missioncontrol/lib/pomodoro.c
