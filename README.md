# Wedding favour

This is the software for a custom PCB similar to a Minimus V1 that enumerates
as a USB HID device (keyboard) and runs 5 LEDs in different patterns.  These
can be cycled by sending CapsLock LED status messages, which are typically done
by the operating system to keep this "keyboard" in sync with any others
connected to the computer.

## Dependencies

* This uses the LUFA stack dated 2014-09-28 to provide USB support
* GCC-AVR is needed to compile the code.  I used 4.8.1.
* `dfu-programmer` to load the code via bootloader

More to come...
