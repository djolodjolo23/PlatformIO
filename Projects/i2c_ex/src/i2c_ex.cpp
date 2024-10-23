#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "AppMultisensor.hpp"

extern "C" void app_main(void) {
    // Delay for 10 seconds (or adjust as needed) before starting
    printf("\nWaiting for 5 seconds before starting AppMultisensor...\n");
    vTaskDelay(5000 / portTICK_PERIOD_MS);

    printf("Starting AppMultisensor...\n");
    app::AppMultisensor multisensor;
    multisensor.init();

    while (true) {
        printf("Reading sensor data...\n");
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        auto reading = multisensor.read();

        ESP_LOGI(__func__, "lux: %.2f",
                 reading.lux);
    }
}
