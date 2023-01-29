This is my version of a non-invasive power meter.

This is heavily inspired by:

https://github.com/klaasnicolaas/home-assistant-glow

I have changed the led to a single ws2812b led and have added some homegrown features to the code.

Restoring the Total Pulse Count at boot. Saving it in an Global Variable (with Restore set to yes) and using it at boot.
Added a way to get warnings with high or abnormal power consumption levels. A binary_sensor will indicate a problem if level is above a specified level.
Added an internal_filter at 50ms to the pulse_meter. The photoelectric sensor can be noisy and I've found the filter is needed, in order not to get crazy spikes.
Added a way to track usage with a start reading. You specify the start reading and the code will use that to tell you current usage.
Added a red/green light function to led (if enabled). Green at low level and more and more red as we approach the problem level specified.
