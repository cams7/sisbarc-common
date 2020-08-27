# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES 
	esp_http_server 
	nvs_flash 
	json
)
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c" "app_common.c" "app_connect.c" "app_httpd_common.c")
#set(COMPONENT_SRCS "app_common.c" "app_connect.c" "app_httpd_common.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()