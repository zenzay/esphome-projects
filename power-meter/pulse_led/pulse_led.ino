// pulse_led - simulate the pulse led on a power panel
const float pulse_rate = 1000.0f;   // number of blinks per kWh
const float wattage = 1000.0f;      // power consumption to simulate
const uint32_t interval_ms = ( 1000.0f / pulse_rate ) * ( 1000.0f / wattage ) * 3600.0f;  // blink interval
uint32_t last_ms = 0;              // last blink millis
uint32_t now_ms = 0;               // current millis
int led_state = LOW;               // initial led state
const int led_pin = 16;            // gpio pin number of led
const int led_on_ms = 100;         // led on duration

void setup() {
  pinMode(led_pin, OUTPUT);
  last_ms = millis();
}

void loop() {
  now_ms = millis();
  if ( (now_ms - last_ms) > interval_ms) {
    led_state = !led_state;
    digitalWrite(led_pin, led_state);
    last_ms = now_ms;
  } else if (led_state == HIGH) {
    if ( (now_ms - last_ms) >= led_on_ms) {
      led_state = !led_state;
      digitalWrite(led_pin, led_state);
    }
  }
}
