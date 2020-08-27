/*
 * app_common.h
 *
 *  Created on: 22 de ago de 2020
 *      Author: ceanm
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "float.h"
#include "esp_log.h"
#include "cJSON.h"

#ifdef CONFIG_IDF_TARGET_ESP32
#define CHIP_NAME "ESP32"
#else
#define CHIP_NAME "UNKNOWN"
#endif

#define APP_COMMON_TAG "app_common"

#define APP_ERROR_CHECK_WITH_MSG(valid, message, goto_tag, ...)                                        \
    do {                                                                                               \
        if (!(valid)) {                                                                                \
			if(*message != '\0')                                                                       \
            	ESP_LOGE(APP_COMMON_TAG, "%s(%d): " message, __FUNCTION__, __LINE__, ##__VA_ARGS__);   \
            goto goto_tag;                                                                             \
        }                                                                                              \
    } while (0)

#define APP_ERROR_CHECK(valid, goto_tag, ...)                                                         \
    do {                                                                                              \
        if (!(valid)) {                                                                               \
			goto goto_tag;                                                                            \
		}                                                                                             \
    } while (0)

#define APP_ERROR(goto_tag, ...)                                                                      \
    do {                                                                                              \
        goto goto_tag;                                                                                \
    } while (0)

#define JSON_ATTR_FALSE 0
#define JSON_ATTR_TRUE 1

#define JSON_INT_ATTR_NOTFOUND INT_MIN
#define JSON_DOUBLE_ATTR_NOTFOUND DBL_MIN
#define JSON_STRING_ATTR_NOTFOUND NULL

#define JSON_GET_INT(object, string) (cJSON_GetObjectItem(object, string) != NULL ? cJSON_GetObjectItem(object, string)->valueint : JSON_INT_ATTR_NOTFOUND)
#define JSON_GET_DOUBLE(object, string) (cJSON_GetObjectItem(object, string) != NULL ? cJSON_GetObjectItem(object, string)->valuedouble : JSON_DOUBLE_ATTR_NOTFOUND)
#define JSON_GET_STRING(object, string) (cJSON_GetObjectItem(object, string) != NULL ? cJSON_GetObjectItem(object, string)->valuestring : JSON_STRING_ATTR_NOTFOUND)

#ifdef __cplusplus
}
#endif
