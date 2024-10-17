#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "AppButton.hpp"
#include "AppLed.hpp"

extern "C" void app_main()
{
    app::AppLed led;
    led.init();
    while (true)
    {
        led.blink();
    }
    vTaskSuspend(nullptr);
}