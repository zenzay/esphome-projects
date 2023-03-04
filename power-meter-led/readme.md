# Power Meter LED #

## A ESPHome custom component that attempts to simulate the flashing LED on a Power Meter. ##

These LEDs usually pulse with either 1000 or 10000 pulses per kWh, and thus we can simulate this with our own LED and an ESP32.

The custom component allows you to set *Pulse Rate* and to set the *Power Use* (consumption) to simulate, using a couple of Number components.

It also has an enable switch, which you have to flip to get some action.

### Instructions ###

Attach a LED to pin 16 on an ESP32 (remember resistor) and copy power_meter_led.h to your ESPHome folder.

Note: If you want to use another pin, you'll have to edit power_meter_led.h.
