#pragma once

#include <bmp280.h>
#include <cstring>

namespace app {
    struct SensorReading {
        float pressure;
        float temperature;
        float humidity;
        // float lux;  // Commented out as we are not using the light sensor
    };

    class AppMultisensor {
    private:
        // tsl2591_t m_light_sensor;  // Commented out as we are not using the light sensor
        bmp280_t m_temp_sensor;
        bmp280_params_t m_bmp280_params;

    public:
        void init(void) {
            ESP_ERROR_CHECK(i2cdev_init());
            // Commented out the TSL2591 initialization
            /*
            memset(&m_light_sensor, 0, sizeof(tsl2591_t));
            ESP_ERROR_CHECK(tsl2591_init_desc(&m_light_sensor, I2C_NUM_1,
                                              GPIO_NUM_41, GPIO_NUM_40));
            ESP_ERROR_CHECK(tsl2591_init(&m_light_sensor));
            */
            memset(&m_temp_sensor, 0, sizeof(bmp280_t));
            ESP_ERROR_CHECK(bmp280_init_default_params(&m_bmp280_params));
            ESP_ERROR_CHECK(bmp280_init_desc(&m_temp_sensor,
                                             BMP280_I2C_ADDRESS_1, I2C_NUM_1,
                                             GPIO_NUM_41, GPIO_NUM_40));
            ESP_ERROR_CHECK(bmp280_init(&m_temp_sensor, &m_bmp280_params));
        }

        SensorReading read(void) {
            SensorReading reading;
            bmp280_read_float(&m_temp_sensor, &reading.temperature, &reading.pressure, &reading.humidity);
            // tsl2591_get_lux(&m_light_sensor, &reading.lux);  // Commented out as we are not using the light sensor
            return reading;
        }
    };
}
