#pragma once
#include <functional>
#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "driver/gpio.h"

namespace
{
    void button_handler(void *arg);
}

namespace app
{
    class AppButton
    {
        private:
            bool state;
            std::function<void(bool)> pressedHandler;
        public:
            AppButton(std::function<void(bool)> h) : state(false),
            pressedHandler(h) {}

        
        void init(void){
            gpio_config_t config;
            config.pin_bit_mask = (1ULL << GPIO_NUM_38);
            config.mode = GPIO_MODE_INPUT;
            config.pull_up_en = GPIO_PULLUP_ENABLE;
            config.pull_down_en = GPIO_PULLDOWN_DISABLE;
            config.intr_type = GPIO_INTR_NEGEDGE;
            gpio_config(&config);
            gpio_install_isr_service(0);
            gpio_isr_handler_add(GPIO_NUM_38, button_handler, this);
        }

        void toogle(void){
            state = !state;
            pressedHandler(state);
        }
    }; // end of class


} // end of namespace

namespace
{
    IRAM_ATTR void button_handler(void *arg)
    {
        static volatile TickType_t next = 0;
        TickType_t now = xTaskGetTickCountFromISR();
        if (now >= next)
        {
            auto btn = reinterpret_cast<app::AppButton *>(arg);
            btn->toogle();
            next = now + 500 / portTICK_PERIOD_MS;
        }
    }
}