/* Copyright 2023 Elliot Powell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"


#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270; // flips the display to show images virtically
    if (!is_keyboard_master()) {
        return OLED_ROTATION_0;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}


// I'd like to have multiple images display at once on the OLED screen

static void render_layer_header(void) {
    static const char PROGMEM kb_layer_header[] = {
        // 'left_oled_layer_only', 32x10px
        0xff, 0x01, 0x01, 0x01, 0xfd, 0x81, 0x81, 0x81, 0x01, 0xf1, 0x4d, 0x39, 0xc1, 0x01, 0x0d, 0xf1,
        0x19, 0x05, 0x01, 0xfd, 0xa5, 0xa5, 0x85, 0x01, 0xfd, 0x25, 0x25, 0xd9, 0x01, 0x01, 0x01, 0xff,
        0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
        0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03
    };
    oled_write_raw_P(kb_layer_header, sizeof(kb_layer_header));
}


static void render_layer_main(bool status) {
    oled_set_cursor(0, 2);
    if (status) {
        static const char PROGMEM kb_layer_main_on[] = {
            // 'left_oled_main_only_on', 32x10px
            0xaa, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0x02, 0xf7, 0xce, 0xf7, 0x02, 0xff, 0x1e, 0xc7, 0xda, 0xc7,
            0x1e, 0xff, 0x7a, 0x03, 0x7a, 0xff, 0x02, 0xf3, 0xce, 0x3f, 0x02, 0xff, 0xfe, 0xff, 0xfe, 0x55,
            0x02, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
            0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01
        };
        oled_write_raw_P(kb_layer_main_on, sizeof(kb_layer_main_on));
    } else {
        static const char PROGMEM kb_layer_main_off[] = {
            // 'left_oled_main_only_off', 32x10px
            0xaa, 0x01, 0x00, 0x01, 0x00, 0x01, 0xfc, 0x09, 0x30, 0x09, 0xfc, 0x01, 0xe0, 0x39, 0x24, 0x39,
            0xe0, 0x01, 0x84, 0xfd, 0x84, 0x01, 0xfc, 0x0d, 0x30, 0xc1, 0xfc, 0x01, 0x00, 0x01, 0x00, 0x55,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x01,
        };
        oled_write_raw_P(kb_layer_main_off, sizeof(kb_layer_main_off));
    }
}

static void render_layer_vim(bool status) {
    oled_set_cursor(0, 4);
    if (status) {
        static const char PROGMEM kb_layer_vim_on[] = {
            // 'left_oled_vim_only_on', 32x10px
            0xaa, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xe2, 0x9f, 0x7e, 0x9f, 0xe2, 0xff, 0xfe, 0xff, 0xfe, 0x0b,
            0xfe, 0xff, 0xfe, 0xff, 0x06, 0xef, 0x8e, 0xef, 0x0e, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x55,
            0x02, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
            0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01
        };
        oled_write_raw_P(kb_layer_vim_on, sizeof(kb_layer_vim_on));
    } else {
        static const char PROGMEM kb_layer_vim_off[] = {
            // 'left_oled_vim_only_off', 32x10px
            0xaa, 0x01, 0x00, 0x01, 0x00, 0x01, 0x1c, 0x61, 0x80, 0x61, 0x1c, 0x01, 0x00, 0x01, 0x00, 0xf5,
            0x00, 0x01, 0x00, 0x01, 0xf8, 0x11, 0x70, 0x11, 0xf0, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x55,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x01,
        };
        oled_write_raw_P(kb_layer_vim_off, sizeof(kb_layer_vim_off));
    }
}


static void render_layer_numpad(bool status) {
    oled_set_cursor(0, 6);
    if (status) {
        static const char PROGMEM kb_layer_numpad_on[] = {
            // 'left_oled_num_only_on', 32x10px
            0xaa, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x03, 0xf2, 0xcf, 0x3e, 0x03, 0xfe, 0xff, 0x02, 0x7f,
            0x7e, 0x03, 0xfe, 0xff, 0x02, 0xe7, 0x9e, 0xe7, 0x02, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0x55,
            0x02, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
            0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01, 0x03, 0x01,
        };
        oled_write_raw_P(kb_layer_numpad_on, sizeof(kb_layer_numpad_on));
    } else {
        static const char PROGMEM kb_layer_numpad_off[] = {
            // 'left_oled_num_only_off', 32x10px
            0xaa, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0xfd, 0x0c, 0x31, 0xc0, 0xfd, 0x00, 0x01, 0xfc, 0x81,
            0x80, 0xfd, 0x00, 0x01, 0xfc, 0x19, 0x60, 0x19, 0xfc, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x55,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00,
            0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x01,
        };
        oled_write_raw_P(kb_layer_numpad_off, sizeof(kb_layer_numpad_off));
    }
}

void horizontal_line(uint8_t y) {
    for (uint8_t x = 0; x < 32; x++) {
        oled_write_pixel(x, y, true);
    }
}

// function to render the layer images
void oled_render_layers(void) {
    render_layer_header();
    switch (get_highest_layer(layer_state)) {
        case 0:
            render_layer_main(true);
            render_layer_vim(false);
            render_layer_numpad(false);
            break;
        case 1:
            render_layer_main(false);
            render_layer_vim(true);
            render_layer_numpad(false);
            break;
        case 2:
            render_layer_main(false);
            render_layer_vim(false);
            render_layer_numpad(true);
            break;
    }
    horizontal_line(64);
}

void get_kb_led_status_caps_lock(void) {
    bool caps = host_keyboard_led_state().caps_lock;
    oled_write_P(PSTR("CAPS\n"), false);
    switch (caps) {
        case 0:
            oled_write_ln_P(PSTR("Off"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("On"), false);
            break;
    }

}

void get_kb_led_status_num_lock(void) {
    bool numlck = host_keyboard_led_state().num_lock;
    oled_write_P(PSTR("NUMLK"), false);
    switch (numlck) {
        case 0:
            oled_write_ln_P(PSTR("Off"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("On"), false);
            break;
    }

}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if (is_keyboard_master()) {
        oled_render_layers();
    } else {
        get_kb_led_status_caps_lock();
        oled_write_ln_P(PSTR("\n"), false);
        get_kb_led_status_num_lock();
    }
    return false;
}

#endif // OLED_ENABLE
