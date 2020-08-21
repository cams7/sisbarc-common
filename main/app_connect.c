/*
 * app_connect.c
 *
 *  Created on: 21 de ago de 2020
 *      Author: ceanm
 */

#include "app_connect.h"

#include "esp_log.h"
#include "esp_err.h"

static const char *TAG = "app_connect";

esp_err_t app_connect(void) {
	ESP_LOGI(TAG, "A funcionalidade app_connect foi executada");
	return ESP_OK;
}

esp_err_t app_disconnect(void) {
	ESP_LOGI(TAG, "A funcionalidade app_disconnect foi executada");
	return ESP_OK;
}
