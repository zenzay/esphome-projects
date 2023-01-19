#include "esphome.h"
#include <SparkFun_GridEYE_Arduino_Library.h>

class AMG8833DebugComponent : public PollingComponent
{
public:
    AMG8833DebugComponent() : PollingComponent(2000) {}
    Sensor *hot_pixels = new Sensor();
    Sensor *warm_pixels = new Sensor();
    Sensor *device_temp = new Sensor();
    Sensor *max_temp = new Sensor();
    Sensor *min_temp = new Sensor();
    Sensor *range_temp = new Sensor();
    Sensor *avg_temp = new Sensor();

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
        float pixel_temp;
        float min = 100000;
        float max = 0;
		float avg = 0;
		unsigned char hot_count = 0; 	// pixel is above device temperature counter
		unsigned char warm_count = 0;	// pixel is above minimum temperature + x degrees counter
		unsigned char min_index = 0;	// not really used or published (yet)
		unsigned char max_index = 0;    // not really used or published (yet)
		float dev_temp = grideye.getDeviceTemperature() - dev_temp_offset;
		
		// find minimum, maximum and average temperatures and count 'hot' pixels
        for (unsigned char i = 0; i < total_pixels; i++)
		{
            pixel_temp = grideye.getPixelTemperature(i);
            if (pixel_temp < min)
			{
                min = pixel_temp;
				min_index = i;
            }
			else if (pixel_temp > max)
			{
                max = pixel_temp;
				max_index = i;
            }
			
			if (pixel_temp >= dev_temp)
			{
                hot_count++;
			}
			avg += pixel_temp;
        }
		avg = avg / total_pixels;
		
		// run through grid again to find the 'warm' pixels.
        for (unsigned char i = 0; i < total_pixels; i++)
		{
            pixel_temp = grideye.getPixelTemperature(i);
            if (pixel_temp > (min + min_diff_temp))
			{
                warm_count++;
            }
        }

		// publish the lot
        max_temp->publish_state(max);
        min_temp->publish_state(min);
        range_temp->publish_state(max - min);		
		hot_pixels->publish_state(hot_count * 100 / total_pixels);
		warm_pixels->publish_state(warm_count * 100 / total_pixels);
		device_temp->publish_state(dev_temp);
		avg_temp->publish_state(avg);
		
		// todo: use min_index to figure out whether it's close to max_index to filter out weird spikes?
		// todo: maybe try to figure out whether the hot/warm pixels are clustered... by looking a neighbours to see if some of them are also hot/warm
		// ...somehow?!
		// x = i%size;
		// y = i/size;
		// if ( x > 0 ) .. look at pixel to the left
		//    j = y * size + (x - 1)
		// else if ( x < (size-1) ) .. look at pixel to the right
		//    j = y * size + (x + 1)
		// Hmm... I wonder if the ESP can handle the load.. the detection routine is supposed to be called every 100ms
		// and you would have to look at something like 4+ neighbours with every pixel going through the loop
		// this would make it much more demanding on the ESP and.... hmm can it take it capt'n?
    }

protected:
    GridEYE grideye;
    static const int size = 8;
    static const int total_pixels = size * size;
	static const int min_diff_temp = 4;		// minimum degrees above miminum temperature required to make pixel count as warm
	static const int dev_temp_offset = 3;   // degrees to offset (suctract from) the device temperature tp get reasonable results
};
