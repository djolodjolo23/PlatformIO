#pragma once

#include <tsl2591.h>
#include <bmp280.h>
#include <cstring>


namespace app {
    struct SensorReading {
        float pressure;
        float temperature;
        float humidity;
        float lux;
    };

    class AppMultisensor {
    private:
        tsl2591_t m_light_sensor;
        //tsl2561_t m_light_sensor2;
        bmp280_t m_temp_sensor;
        bmp280_params_t m_bmp280_params;


    public:
        void init(void) {
            ESP_ERROR_CHECK(i2cdev_init());
            memset(&m_light_sensor, 0, sizeof(tsl2591_t));
            ESP_ERROR_CHECK(tsl2591_init_desc(&m_light_sensor,I2C_NUM_1,
                                              GPIO_NUM_41, GPIO_NUM_40));
            ESP_ERROR_CHECK(tsl2591_init(&m_light_sensor));
            //ESP_ERROR_CHECK(bmp280_init_default_params(&m_bmp280_params));
            //ESP_ERROR_CHECK(bmp280_init_desc(&m_temp_sensor,
            //                                 BMP280_I2C_ADDRESS_1, I2C_NUM_1,
             //                                GPIO_NUM_41, GPIO_NUM_40));
            //ESP_ERROR_CHECK(bmp280_init(&m_temp_sensor, &m_bmp280_params));
        
        }

        SensorReading read(void) {
        SensorReading reading;
        memset(&reading, 0, sizeof(SensorReading));

        uint16_t channel0 = 0, channel1 = 0;
        esp_err_t raw_data_result = tsl2591_get_channel_data(&m_light_sensor, &channel0, &channel1);

        if (raw_data_result == ESP_OK) {
            esp_err_t lux_result = tsl2591_calculate_lux(&m_light_sensor, channel0, channel1, &reading.lux);
            if (lux_result != ESP_OK) {
                printf("Failed to calculate lux: %s\n", esp_err_to_name(lux_result));
                reading.lux = 0;
            }
        } else {
            printf("Failed to read channels: %s\n", esp_err_to_name(raw_data_result));
            reading.lux = 0;
        }

        return reading;
    }
        
    };
}