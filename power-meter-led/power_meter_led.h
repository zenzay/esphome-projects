#include "esphome.h"

#define LED_PIN 16
#define LED_ON 100

class PowerMeterLEDComponent : public Component
{
public:
  unsigned long last_pulse;
  unsigned long pulse_width;
  bool enable = false;
  int led_state = LOW;
  float pulse_rate = 1000.0;
  float power_use = 1000.0;

  PowerMeterLEDComponent(esphome::template_::TemplateSwitch *&_enable, esphome::template_::TemplateNumber *&_pulse_rate, esphome::template_::TemplateNumber *&_power_use)
  {
    _enable->add_on_state_callback([this](bool state) { enable = state; });
    _pulse_rate->add_on_state_callback([this](float state) { this->set_new_pulse_rate_(state); });
    _power_use->add_on_state_callback([this](float state) { this->set_new_power_use_(state); });
  }

  void set_new_pulse_rate_(float state)
  {
    pulse_rate = state;
    set_pulse_width();
  }

  void set_new_power_use_(float state)
  {
    power_use = state;
    set_pulse_width();
  }

  void set_pulse_width()
  {
    pulse_width = ( 1000.0 / pulse_rate ) * ( 1000.0 / power_use ) * 3600.0;
    ESP_LOGD("custom", "new pulse width: %d", pulse_width);
  }

  void setup() override
  {
    pinMode(LED_PIN, OUTPUT);
    set_pulse_width();
    last_pulse = millis();
  }

  void loop() override
  {
    if (enable == false) {
      delay(100);
      return;
    }
    unsigned long now = millis();
    if ((now - last_pulse) > pulse_width)
    {
      led_state = !led_state;
      digitalWrite(LED_PIN, led_state);
      last_pulse = now;
    }
    else if (led_state == true)
    {
      if ((now - last_pulse) > LED_ON)
      {
        led_state = !led_state;
        digitalWrite(LED_PIN, led_state);
      }
    }
  }
};
