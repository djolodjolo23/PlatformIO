#pragma once

#include <tsl2591.h>
#include <bmp280.h>

namespace app{
    struct SensorReading
    {
        float pressure;float temperature;float humidity;float lux;
        /* data */
    };
    
    class AppMultisensor
    {
    private:
        tsl2561_t m_light_sensor;
        bmp280_t m_temp_sensor;
        bmp280_params_t m_bmp280_params;
    public:
        AppMultisensor(/* args */);
        ~AppMultisensor();
    };
    
    AppMultisensor::AppMultisensor(/* args */)
    {
    }
    
    AppMultisensor::~AppMultisensor()
    {
    }
    
}