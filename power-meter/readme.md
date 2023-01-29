This is my version of a non-invasive power meter.

I've used Home Assistant Glow for a while without problems. Suddenly I start to get crazy high spikes, in the reported power consumption, every day at around the same time (weird). I had to chase that down and started to look at the code. This is the result.

The excellent Home Assistant Glow can be found here:

https://github.com/klaasnicolaas/home-assistant-glow

I changed the led to a single ws2812b led and have added some homegrown features to the code.

1. Restoring the Total Pulse Count at boot. Saving it in an Global Variable (with Restore set to yes) and using it at boot.
2. Added a way to get warnings with high or abnormal power consumption levels. A binary_sensor will indicate a problem if level is above a specified level.
3. Added an internal_filter at 50ms to the pulse_meter. The photoelectric sensor can be noisy and I've found the filter is needed, in order not to get crazy spikes.
4. Added a way to track usage with a start reading. You specify the start reading and the code will use that to tell you current usage.
5. Added a red/green light function to led (if enabled). Green at low level and more and more red as we approach the problem level specified.
