#pragma once

#include "config_common.h"

#define VENDOR_ID       0xABCD
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    Roman Oskolkov
#define PRODUCT         Macropad

#define MATRIX_ROWS 2
#define MATRIX_COLS 2

#define ENCODERS_PAD_A { B4 }
#define ENCODERS_PAD_B { B5 }
#define DIP_SWITCH_PINS { B6 }

#define MATRIX_ROW_PINS { B1, B3 }
#define MATRIX_COL_PINS { C6, D7 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5


#define OLED_DISPLAY_128X64
#define OLED_FADE_OUT 2000
