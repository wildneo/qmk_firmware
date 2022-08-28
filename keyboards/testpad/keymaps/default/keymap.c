#include QMK_KEYBOARD_H
#include "testpad.h"
#include "config.h"

enum Encoder { ENC1 };
enum DipSwitch { ENCSW1 };

enum Layers {
    L1,
    L2,
    L3,
    _layers_length
};

enum EncoderMode {
    LAYER,
    SCROLL,
    VOLUME,
    _encoder_modes_length,
};

static enum EncoderMode current_encoder_mode = LAYER;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L1] = LAYOUT(
        KC_1,  KC_2,    \
        KC_3,  KC_4     \
    ),
    [L2] = LAYOUT(
        KC_5,   KC_6,   \
        KC_7,   KC_8    \
    ),
    [L3] = LAYOUT(
        KC_9,   KC_0,   \
        KC_A,   KC_B    \
    )
};

void draw_layer_status(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case L1:
            oled_write_ln_P(PSTR("L1"), false);
            break;
        case L2:
            oled_write_ln_P(PSTR("L2"), false);
            break;
        case L3:
            oled_write_ln_P(PSTR("L3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

void draw_encoder_status(void) {
    oled_write_P(PSTR("Encoder mode: "), false);
    switch (current_encoder_mode) {
        case LAYER:
            oled_write_ln_P(PSTR("LAYER"), false);
            break;

        case SCROLL:
            oled_write_ln_P(PSTR("SCROLL"), false);
            break;

        case VOLUME:
            oled_write_ln_P(PSTR("VOLUME"), false);
            break;

        default:
            oled_write_ln_P(PSTR("Undefined"), false);
            break;
    }
}

void draw_layer_commands(void) {
    switch (get_highest_layer(layer_state)) {
        case L1:
            oled_write_P(PSTR("L1CMD1 "), false);
            oled_write_P(PSTR("L1CMD2 "), false);
            oled_write_ln_P(PSTR("L1CMD3"), false);

            oled_write_P(PSTR("L1CMD4 "), false);
            oled_write_P(PSTR("L1CMD5 "), false);
            oled_write_ln_P(PSTR("L1CMD6"), false);

            oled_write_P(PSTR("L1CMD7 "), false);
            oled_write_P(PSTR("L1CMD8 "), false);
            oled_write_ln_P(PSTR("L1CMD9"), false);
            break;

        case L2:
            oled_write_P(PSTR("L2CMD1 "), false);
            oled_write_P(PSTR("L2CMD2 "), false);
            oled_write_ln_P(PSTR("L2CMD3"), false);

            oled_write_P(PSTR("L2CMD4 "), false);
            oled_write_P(PSTR("L2CMD5 "), false);
            oled_write_ln_P(PSTR("L2CMD6"), false);

            oled_write_P(PSTR("L2CMD7 "), false);
            oled_write_P(PSTR("L2CMD8 "), false);
            oled_write_ln_P(PSTR("L2CMD9"), false);
            break;

        case L3:
            oled_write_P(PSTR("L3CMD1 "), false);
            oled_write_P(PSTR("L3CMD2 "), false);
            oled_write_ln_P(PSTR("L3CMD3"), false);

            oled_write_P(PSTR("L3CMD4 "), false);
            oled_write_P(PSTR("L3CMD5 "), false);
            oled_write_ln_P(PSTR("L3CMD6"), false);

            oled_write_P(PSTR("L3CMD7 "), false);
            oled_write_P(PSTR("L3CMD8 "), false);
            oled_write_ln_P(PSTR("L3CMD9"), false);
            break;

        default:
            break;
    }
}

void draw_led_status(void) {
    oled_write_P(host_keyboard_led_state().num_lock ? PSTR(" NUM   ") : PSTR("       "), false);
    oled_write_P(host_keyboard_led_state().caps_lock ? PSTR(" CAP   ") : PSTR("       "), false);
    oled_write_P(host_keyboard_led_state().scroll_lock ? PSTR(" SCR   ") : PSTR("       "), false);
}

bool oled_task_user(void) {
    draw_layer_status();
    draw_encoder_status();
    oled_advance_page(true);

    draw_layer_commands();
    oled_advance_page(true);

    draw_led_status();

    return false;
}

uint8_t increment_counter(uint8_t value, uint8_t maxValue) {
    return (value < maxValue) ? value + 1 : 0;
}

uint8_t decrement_counter(uint8_t value, uint8_t maxValue) {
    return (value <= 0) ? maxValue : value - 1;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (!is_oled_on()) return false;

    switch (current_encoder_mode) {
        case LAYER:
            layer_move(clockwise
                ? increment_counter(get_highest_layer(layer_state), _layers_length - 1)
                : decrement_counter(get_highest_layer(layer_state), _layers_length - 1)
            );
            break;

        case SCROLL:
            tap_code(clockwise ? KC_MS_WH_DOWN : KC_MS_WH_UP);
            break;

        case VOLUME:
            tap_code(clockwise ? KC_VOLU : KC_VOLD);
            break;

        default:
            break;
    }

    return false;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case ENCSW1:
            if (active) {
                current_encoder_mode = increment_counter(current_encoder_mode, _encoder_modes_length - 1);
            }
            break;

        default:
            break;
    }

    return false;
}
