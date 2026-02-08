# tenax

![tenax](https://github.com/heyitscassio/tenax/raw/master/pics/1.jpg)

*Tenax is a direct pin/diodeless split keyboard, based on the Blackpill dev board. with pinkie splay.*

* Keyboard Maintainer: [Cássio Ávila](https://github.com/heyitscassio)
* Hardware Supported: *Custom PCB with Weact Blackpills*
* Hardware Availability: [Tenax PCB github repository](https://github.com/heyitscassio/tenax)

Make example for this keyboard (after setting up your build environment):

    make tenax:default

Flashing example for this keyboard:

    make tenax:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Physical reset buttons**: [Enter bootloader](https://github.com/WeActStudio/WeAct_HID_Bootloader_F4x1?tab=readme-ov-file#enter-the-bootloader-method)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
