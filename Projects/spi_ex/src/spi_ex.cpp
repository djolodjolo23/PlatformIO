#include <cinttypes>
#include "esp_log.h"

#include "AppSensor.hpp"
#include "AppStorage.hpp"

namespace {

    app::AppStorage storage;
    app::AppSensor sensor;
}

extern "C" void app_main(void) {

    if (storage.init() == ESP_OK) {
        auto fn = [] (const uint8_t *data, size_t len) {
            storage.save(data, len);
        };
        sensor.init(fn);
    } else {

        ESP_LOGE(__func__, "Failed to initialize storage.");
    }
}