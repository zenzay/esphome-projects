Power Meter
===========

This is my version of a non-invasive power meter.

I've used [Home Assistant Glow](https://github.com/klaasnicolaas/home-assistant-glow) for a while without problems. Suddenly I start to get crazy high spikes, in the reported power consumption, every day at around the same time (weird). I had to chase that down and started to look at the code. This is the result.

My version tries to track both usage and costs.

I've doing a hourly, daily and total counts.

The kWh price is imported as a sensor from Home Assistant, but can also be set 'manually'.

I've added a RTC Module in order to not miss time-events (on the hour, midnight and so on). This way I can be reasonable sure to not miss anything when I'm fiddling with Home Assistant. I probably shouldn't rely on Cron to track time events, but then again, this whole thing should probably be a custom component.

Latest version adds a Waveshare 2.9" E-Ink Display and a push button (to turn pages on the display). For that reason I've implemented a Today Graph for both usage and costs on the display.

Please bear in mind that this is work in progress and a lot of the code is quite kludgy

For testing purposes, I created a 'dummy' pulse meter - a simple led pulsing at specified interval to simulate power consumption. You'll find it in the pulse_led folder.

