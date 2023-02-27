// pulse_led - simulate the pulse led on a power panel
const float pulse_rate = 1000.0f;        // number of blinks per kWh
const float watt_target = 1000.0f;       // power consumption to simulate - overridden if randomize flag is set
const bool random_watt = false;           // randomize wattage
const uint32_t rnd_interval = 60000;     // randomize wattage every 60 seconds
const uint32_t pulse_min_ms = 720;       // min pulse interval when randomizing. 720ms = 5000w at pulse rate 1000 and 500w at pulse rate 10000
const uint32_t pulse_max_ms = 7200;      // max pulse interval when randomizing. 7200ms = 500w at pulse rate 1000 and 50w at pulse rate 10000
const int led_pin = 16;                  // gpio pin number of led
const int led_on_duration = 100;         // led on duration in millis
uint32_t blink_interval = 0;             // blink interval in milliseconds
uint32_t last_blink = 0;                 // last blink millis
uint32_t last_random = 0;                // last randomize millis
uint32_t now = 0;                        // current millis
int led_state = LOW;                     // initial led state

void setup() {
  pinMode(led_pin, OUTPUT);
  last_blink = millis();
  if (random_watt) {
    last_random = last_blink;
    blink_interval = random(pulse_min_ms, pulse_max_ms);
  } else {
    blink_interval =  ( 1000.0f / pulse_rate ) * ( 1000.0f / watt_target ) * 3600.0f;
  }
}

void loop() {
  now = millis();
  if ( (now - last_blink) > blink_interval) {
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
    if (random_watt) {
      if ( (now - last_random) > rnd_interval) {
        last_random = now;
        blink_interval = random(pulse_min_ms, pulse_max_ms);  // get a new random blink interval
      }
      blink_interval += random(-60, 60);  // make it fluctuate a bit so the watt changes with (almost) every pulse
    }    
    last_blink = now;
  } else if (led_state == HIGH) {
    if ( (now - last_blink) >= led_on_duration) {
      led_state = !led_state;
      digitalWrite(led_pin, led_state);
    }
  }
}
