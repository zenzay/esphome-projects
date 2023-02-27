Power Meter
===========

This is my version of a non-invasive power meter, using ESPHome. 

I've used [Home Assistant Glow](https://github.com/klaasnicolaas/home-assistant-glow) for a while without problems. Suddenly I start to get crazy high spikes, in the reported power consumption, every day at around the same time (weird). I had to chase that down and started to look at the code. This is the result. The problem btw. was not with HA Glow or ESPHome but a suddenly very noisy Photodiode.

My version tries to track both usage and costs - doing a hourly, daily and total counts.

The kWh price is imported as a sensor from Home Assistant, but can also be set 'manually'.

I've added a RTC Module in order to not miss time-events (on the hour, midnight and so on). This way I can be reasonable sure to not miss anything when I'm fiddling with Home Assistant. I probably shouldn't rely on Cron to track time events, but then again, this whole thing should probably be a custom component.

Latest version adds a Waveshare 2.9" E-Ink Display and a push button (to turn pages on the display). For that reason I've implemented a **Today Graph** for both usage and costs on the display.

For testing purposes, I created a 'dummy' pulse meter - a simple led pulsing at specified interval to simulate power consumption. You'll find it in the [pulse_led](./pulse_led/) folder.

*Please bear in mind that this is work in progress and a lot of the code is quite kludgy.*


Components
-----------

* Wemos D1 Mini ESP32 (any ESP32 should do)
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
