# Lily58 JZ

This is a fork of the Lily58 Pro keyboard, with the following changes:
    - Uses the Elite-C controller instead of the Pro Micro
    - Keyboard layout:
        - Split spacebar
        - Aarow keys on the raised layer
        - 10 key on the 3rd layer

Make example for this keyboard (after setting up your build environment):

    make lily58/jz58:jz_default

Flash example for this keyboard:

    make lily58/jz58:jz_default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

These PCBs have a reset on the underside of the PCB next to the controller which may be pressed to enter in to the bootloader.

Additionally, if you hold down the "ESC" or "GRV" buttons when plugging in that half of the keyboard (per the default QWERTY layout), this will jump to the bootloader and reset the EEPROM (persistent storage).
