Power Meter
===========

Yet another version of a non-invasive power meter, using the [Pulse Meter](https://esphome.io/components/sensor/pulse_meter.html) component in [ESPHome](https://esphome.io/).

I've used [Home Assistant Glow](https://github.com/klaasnicolaas/home-assistant-glow) for a while without problems. Suddenly I start to get crazy high spikes, in the reported power consumption, every day at around the same time (weird). I had to chase that down and started to look at the code. This is the result. The problem btw. was not with HA Glow or ESPHome but a suddenly very noisy Photodiode.

My version tries to track both usage and costs - doing hourly, daily and total counts.

The kWh price is imported as a sensor from Home Assistant, but can also be set 'manually'.

I've added a RTC Module in order to not miss time-events (on the hour, midnight and so on). This way I can be reasonable sure to not miss anything when I'm fiddling with Home Assistant. I probably shouldn't rely on Cron to track time events, but then again, this whole thing should probably be a custom component.

Latest version adds a Waveshare 2.9" E-Ink Display and a push button. The button was to be able to turn pages on the display. First page is a, sort of, Status page and the subsequent pages shows some graphs and stuff.  To make it easier for myself - not wanting to draw every single line on the display - I've created some transparent backgrounds in Gimp, and just pop those on the display before drawing the rest.

Side note: Achieving transparency when drawing images in ESPHome can be tricky. I often ended up with exporting PNGs from GIMP that, to the naked eye, looks like they're fully transparent, but they're apparently not 100% and turn up black on the display. What seemed to fix it was to fill all areas, that I wanted transparent, with white and subsequently Magic Select the areas and delete them. No idea why, but it worked for me.

For testing purposes, I created a 'dummy' pulse meter - a simple led pulsing at specified interval to simulate power consumption. You'll find it in the [pulse_led](./pulse_led/) folder.

*Please bear in mind that this is work in progress and a lot of the code is quite kludgy.*


Components
-----------

* Wemos D1 Mini ESP32 (any ESP32 will do. An ESP8266 *should* work too, but it's not as fast and has fewer pins)
* DS 3131 Real Time Clock Module (DS1307 also works)
* 2.9" E-Ink Display (Waveshare or other)
* Physical Push Button

Wiring
-------

Waveshare 2.9" E-Ink Display
| BOARD PIN | ESP32 PIN |
|----------:|-----------|
|     BUSY  |       19  |
|      RST  |       16  |
|      DC   |       17  |
|      CS   |        5  |
|     CLK   |       18  |
|     DIN   |       23  |
|     GND   |      GND  |
|     VCC   |      3.3v |


DS3231 I2C Real Time Clock Module
| BOARD PIN | ESP32 PIN |
|----------:|-----------|
|      SDA  |       21  |
|      SCL  |       22  |
|      VCC  |      VCC  |
|      GND  |      GND  |

LM393 Photodiode Sensor module
| BOARD PIN | ESP32 PIN |
|----------:|-----------|
|       D0  |       26  |
|       A0  |       NC  |
|      VCC  |      VCC  |
|      GND  |      GND  |

Push Button
|  PIN | ESP32 PIN |
|-----:|-----------|
|   1  |      GND  |
|   2  |       27  |
