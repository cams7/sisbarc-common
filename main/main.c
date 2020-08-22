#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_err.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "app_common.h"
#include "app_connect.h"

#define SISBARC_COMMON_TAG "sisbarc-common"

esp_err_t check_led_level(bool *level) {
	APP_ERROR_CHECK(*level, "Error: LED is off", err_led_off);
	return ESP_OK;
err_led_off:
	return ESP_ERR_INVALID_RESPONSE;
}

void app_main(void) {
	ESP_ERROR_CHECK(nvs_flash_init());
	ESP_ERROR_CHECK(esp_netif_init());
	ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK( app_connect() );

    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    bool level = false;
    while (true) {
    	ESP_LOGI(SISBARC_COMMON_TAG, "LED is %s", check_led_level(&level) == ESP_OK ? "ON" : "OFF");
        gpio_set_level(GPIO_NUM_2, level);
        level = !level;
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}

