#pragma once
#include "driver/gpio.h"
#include "esp_mac.h"

namespace app
{
    class AppLed
    {
        public:
            void init(void)
            {
                gpio_config_t config;
                config.pin_bit_mask = (1ULL << GPIO_NUM_39);
                config.mode = GPIO_MODE_OUTPUT;
                config.pull_up_en = GPIO_PULLUP_DISABLE;
                config.pull_down_en = GPIO_PULLDOWN_DISABLE;
                config.intr_type = GPIO_INTR_DISABLE;
                gpio_config(&config);
            }
        void set(bool val)
        {
        gpio_set_level(GPIO_NUM_39, static_cast<uint32_t>(val));
        }

        void blink(void)
        {
            set(true);
            vTaskDelay(500 / portTICK_PERIOD_MS);
            set(false);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    };
}