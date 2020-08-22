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

#include "esp_log.h"

#define APP_COMMON_TAG "app_common"

#define APP_ERROR_CHECK(a, str, goto_tag, ...)                                             \
    do                                                                                     \
    {                                                                                      \
        if (!(a))                                                                          \
        {                                                                                  \
            ESP_LOGE(APP_COMMON_TAG, "%s(%d): " str, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            goto goto_tag;                                                                 \
        }                                                                                  \
    } while (0)

#ifdef __cplusplus
}
#endif
