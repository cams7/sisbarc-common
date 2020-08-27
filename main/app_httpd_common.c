/*
 * app_httpd_common.c
 *
 *  Created on: 27 de ago de 2020
 *      Author: ceanm
 */

#include "app_common.h"
#include "app_httpd_common.h"

esp_err_t resp_send_json_data(httpd_req_t *req, cJSON *json_data, const char* httpStatus) {
	esp_err_t resp;
	char *data = cJSON_Print(json_data);
	httpd_resp_set_hdr(req, HTTP_HEAD_ALLOW_ORIGIN, "*");
	httpd_resp_set_type(req, CONTENT_TYPE_APPLICATION_JSON);
	httpd_resp_set_status(req, httpStatus);
	resp = httpd_resp_sendstr(req, data);
	free(data);
	return resp;
}

esp_err_t resp_send_json_data_ok(httpd_req_t *req, cJSON *json_data) {
	return resp_send_json_data(req, json_data, _200_OK);
}

esp_err_t resp_send_json_message(httpd_req_t *req, const char* httpStatus, const char* message) {
	cJSON *json_data = cJSON_CreateObject();
	cJSON_AddStringToObject(json_data, "message", message);
	esp_err_t resp = resp_send_json_data(req, json_data, httpStatus);
	cJSON_Delete(json_data);
	return resp;
}

esp_err_t resp_send_json_invalid_content(httpd_req_t *req) {
	esp_err_t resp = resp_send_json_message(req, _400_BAD_REQUEST, ERR_MSG_INVALID_CONTENT);
	return resp;
}

char* getBuffer(httpd_req_t *req, esp_err_t *resp) {
	char *buffer = NULL;
	int total_len = req->content_len;

	if (total_len >= SCRATCH_BUFSIZE) {
		*resp = resp_send_json_message(req, _400_BAD_REQUEST, "Content too long");
		APP_ERROR(err_set_buffer);
	}

	int cur_len = 0;
	buffer = ((rest_server_context_t *)(req->user_ctx))->scratch;

	int received = 0;

	while (cur_len < total_len) {
		received = httpd_req_recv(req, buffer + cur_len, total_len);
		if (received <= 0) {
			*resp = resp_send_json_message(req, _500_INTERNAL_SERVER_ERROR, "Failed to post control value");
			APP_ERROR(err_set_buffer);
		}
		cur_len += received;
	}
	buffer[total_len] = '\0';

	return buffer;
err_set_buffer:
	return NULL;
}

bool validateBetweenIntVal(cJSON *resp_json_err, const char* attr, const int* val, const int16_t min, const int16_t max) {
	bool isValid = true;

	if(*val < min || *val > max) {
		char message[42];
		sprintf(message, "Value should be between %d and %d", min, max);
		cJSON_AddStringToObject(resp_json_err, attr, message);
		isValid = false;
	}

	return isValid;
}

bool validateBoolVal(cJSON *resp_json_err, const char* attr, const int* val) {
	bool isValid = true;

	if(*val != JSON_ATTR_FALSE && *val != JSON_ATTR_TRUE) {
		char message[21];
		sprintf(message, "Value must be %d or %d", JSON_ATTR_FALSE, JSON_ATTR_TRUE);
		cJSON_AddStringToObject(resp_json_err, attr, message);
		isValid = false;
	}

	return isValid;
}

int getAttrIntVal(cJSON *req_json_data, cJSON *resp_json_err, const char* attr, validation_type validationType, bool isOk, bool *hasError, const uint8_t total_args, ...) {
	int val = JSON_GET_INT(req_json_data, attr);
	if (val != JSON_INT_ATTR_NOTFOUND && isOk) {
		switch (validationType) {
			case VAL_BETWEEN: {
				va_list valist;
				va_start(valist, total_args);
				const int min = va_arg(valist, int);
				const int max = va_arg(valist, int);
				va_end(valist);

				if(!validateBetweenIntVal(resp_json_err, attr, &val, min, max))
					*hasError = true;
				break;
			}
			case VAL_BOOL:
				if(!validateBoolVal(resp_json_err, attr, &val))
					*hasError = true;
				break;
			default:
				break;
		}
	}
	return val;
}
