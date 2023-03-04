# Power Meter LED #

## A ESPHome custom component that attempts to simulate the flashing LED on a regular Power Meter. ##

These LEDs usually pulse with either 1000 or 10000 pulses per kWh, and thus we can simulate this with our own LED and an ESP32.

The custom component allows you to set *Pulse Rate* and to set the *Power Use* (consumption) to simulate, using a couple of Number components.

Note: Unfortunately it's apparently not as precise as I hoped. The measured power consumption fluctuates a few watts up and down. I guess it has it's uses, but not for checking accuracy of timing on the other side of the equation. If you want more accurate timing, I'm afraid this wont do and you'll have to hit the hardware more [directly](https://github.com/zenzay/arduino-projects/tree/main/power-meter-pulse-led).

### Instructions ###

Attach a LED to pin 16 on an ESP32 (remember resistor) and copy power_meter_led.h to your ESPHome folder.

Note: If you want to use another pin, you'll have to edit power_meter_led.h.
