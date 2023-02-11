#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

class AMG8833DetectionComponent : public PollingComponent, public BinarySensor
{
public:
    float get_setup_priority() const override { return esphome::setup_priority::BUS; }
    AMG8833DetectionComponent() : PollingComponent(1000) {}

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
        float pixel_temp;
        float min_temp = 0;
	int warm_count = 0;
	// run trough grid and find minimum temperature
        for (unsigned char i = 0; i < total_pixels; i++)
        {
            pixel_temp = grideye.getPixelTemperature(i);
            if (i == 0 || pixel_temp < min_temp)
            {
                min_temp = pixel_temp;
            }
        }
	// run through the grid again to count number of warm pixels
        for (unsigned char i = 0; i < total_pixels; i++)
        {
            pixel_temp = grideye.getPixelTemperature(i);
	    // adjust the hardcoded difference of 3, if needed, to get higher or lower hot pixel counts
            if (pixel_temp > (min_temp + 3))
            {
                warm_count++;
            }
        }

	// adjust the minimum warm count to fit your case (use the debug component to find that)
        if (warm_count > 3)
        {
            if (!last_state)
            {
                publish_state(true);
                delay_count = delay;
            }
            last_state = true;
        }
        else
        {
            if (last_state)
            {
                delay_count--;
                if (delay_count <= 0)
                {
                    publish_state(false);
                    last_state = false;
                }
            }
        }
    }

protected:
    GridEYE grideye;
    static const int size = 8;
    static const int total_pixels = size * size;
    static const int delay = 5;	// delay count * polling interval = 5 seconds (ie. delayed_off: 5s)
    int delay_count = delay;
    bool last_state = false;
};
