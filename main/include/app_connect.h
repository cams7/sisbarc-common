/*
 * app_connect.h
 *
 *  Created on: 21 de ago de 2020
 *      Author: ceanm
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"

esp_err_t app_connect(void);

esp_err_t app_disconnect(void);

#ifdef __cplusplus
}
#endif
