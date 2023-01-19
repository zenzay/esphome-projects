#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

class AMG8833MainComponent : public PollingComponent
{
public:
    AMG8833MainComponent() : PollingComponent(60000) {}
    Sensor *main_temperature = new Sensor();

    float get_setup_priority() const override { return esphome::setup_priority::BUS; }

    void setup() override
    {
        Wire.begin();
        grideye.begin();
    }

    void loop() override
    {
    }

    void update() override
    {
        main_temperature->publish_state(grideye.getDeviceTemperature() - dev_temp_offset );
    }

protected:
    GridEYE grideye;
	static const int dev_temp_offset = 3;   // degrees to offset (suctract from) the device temperature tp get reasonable results
};
