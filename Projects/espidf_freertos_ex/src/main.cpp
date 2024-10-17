#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_log.h>

namespace
{
    QueueHandle_t m_number_queue;
    const constexpr int MAX_COUNT{20};
    const constexpr char *TAG{"app"};
    void producer(void *p);
    void consumer(void *p);
} // end of namespace

extern "C" void app_main()
{
    ESP_LOGI(TAG, "application started");

    // Initialize the queue and check if it was created successfully
    m_number_queue = xQueueCreate(5, sizeof(int));
    if (m_number_queue == nullptr)
    {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }

    // Create producer task and check if creation is successful
    if (xTaskCreate(producer, "producer", 4096, nullptr, 5, nullptr) != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create producer task");
        return;
    }

    // Create consumer tasks and check if creation is successful
    if (xTaskCreate(consumer, "consumer-0", 4096, (void *)0, 5, nullptr) != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create consumer-0 task");
        return;
    }
    
    if (xTaskCreate(consumer, "consumer-1", 4096, (void *)1, 5, nullptr) != pdPASS)
    {
        ESP_LOGE(TAG, "Failed to create consumer-1 task");
        return;
    }

    // Optional: Print task list to verify task creation
    char buffer[256]{0};
    vTaskList(buffer);
    ESP_LOGI(TAG, "\n%s", buffer);

    // Check available heap memory
    ESP_LOGI(TAG, "Free heap size: %d", xPortGetFreeHeapSize());
} // end of app_main

namespace
{
    void producer(void *p)
    {
        int cnt{0};
        vTaskDelay(pdMS_TO_TICKS(500)); // Initial delay
        while (++cnt <= MAX_COUNT)
        {
            if (xQueueSendToBack(m_number_queue, &cnt, portMAX_DELAY) != pdPASS)
            {
                ESP_LOGE(TAG, "Failed to send to queue");
            }
            ESP_LOGI(TAG, "p:%d", cnt);
        }
        ESP_LOGI(TAG, "Producer finished");
        vTaskDelete(nullptr); // Delete task after completion
    } // end of producer

    void consumer(void *p)
    {
        int num;
        while (true)
        {
            if (xQueueReceive(m_number_queue, &num, portMAX_DELAY) == pdPASS)
            {
                ESP_LOGI(TAG, "c%d:%d", (int)p, num);
            }
            else
            {
                ESP_LOGE(TAG, "Failed to receive from queue");
            }
            vTaskDelay(pdMS_TO_TICKS(100)); // Adjust delay for smoother context switching
        }
    } // end of consumer
} // end of namespace
