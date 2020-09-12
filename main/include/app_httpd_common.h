/*
 * app_httpd_common.h
 *
 *  Created on: 27 de ago de 2020
 *      Author: ceanm
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_vfs.h"
#include "esp_http_server.h"
#include "cJSON.h"

#define APP_HTTPD_COMMON_TAG "app_httpd_common"

#define CONTENT_TYPE_TEXT_PLAIN "text/plain"
#define CONTENT_TYPE_TEXT_HTML  "text/html"
#define CONTENT_TYPE_TEXT_XML   "text/xml"
#define CONTENT_TYPE_TEXT_CSS   "text/css"
#define CONTENT_TYPE_APPLICATION_JSON       "application/json"
#define CONTENT_TYPE_APPLICATION_JAVASCRIPT "application/javascript"
#define CONTENT_TYPE_IMAGE_PNG   "image/png"
#define CONTENT_TYPE_IMAGE_JPEG  "image/jpeg"
#define CONTENT_TYPE_IMAGE_XICON "image/x-icon"

#define _200_OK                    "200"
#define _400_BAD_REQUEST           "400"
#define _500_INTERNAL_SERVER_ERROR "500"

#define HTTP_HEAD_ALLOW_ORIGIN "Access-Control-Allow-Origin"

#define ERR_MSG_SOMETHING_WRONG              "Something wrong"
#define ERR_MSG_INVALID_CONTENT              "Invalid content"
#define ERR_MSG_REQ_JSON_DATA_LOADING_BUFFER "An error occurred while loading the buffer"

#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + 128)
#define SCRATCH_BUFSIZE (10240)

typedef struct rest_server_context {
    char base_path[ESP_VFS_PATH_MAX + 1];
    char scratch[SCRATCH_BUFSIZE];
} rest_server_context_t;

typedef enum {
    VAL_BETWEEN, // Validates if a value is between an interval
    VAL_BOOL,    // Validates if a value is 0 or 1
} validation_type;

esp_err_t resp_send_json_data(httpd_req_t *req, cJSON *json_data, const char* httpStatus);

esp_err_t resp_send_json_data_ok(httpd_req_t *req, cJSON *json_data);

esp_err_t resp_send_json_message(httpd_req_t *req, const char* httpStatus, const char* message);

esp_err_t resp_send_json_invalid_content(httpd_req_t *req);

char* getBuffer(httpd_req_t *req, esp_err_t *resp);

bool validateBetweenIntVal(cJSON *resp_json_err, const char* attr, const int* val, const int16_t min, const int16_t max);

bool validateBoolVal(cJSON *resp_json_err, const char* attr, const int* val);

int getAttrIntVal(cJSON *req_json_data, cJSON *resp_json_err, const char* attr, validation_type validationType, bool isOk, bool *hasError, const uint8_t total_args, ...);

esp_err_t common_handler(httpd_req_t *req);

#ifdef __cplusplus
}
#endif
