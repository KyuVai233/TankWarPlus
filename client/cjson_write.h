#pragma once

#include <cJSON.h>

#include <string>

//±‡–¥str+int
inline const std::string& write_cJSON_string_and_int(const std::string& str, int num_int)
{
	std::string str_json;
	cJSON* cJSON_write_str = cJSON_CreateObject();
	cJSON* cJSON_str;
	cJSON* cJSON_num_int;
	if (!cJSON_write_str)
		goto end;

	cJSON_str = cJSON_CreateString(str.c_str());
	if (!cJSON_str)
		goto end;
	cJSON_AddItemToObject(cJSON_write_str, "str", cJSON_str);

	cJSON_num_int = cJSON_CreateNumber(num_int);
	if (!cJSON_num_int)
		goto end;
	cJSON_AddItemToObject(cJSON_write_str, "num_int", cJSON_num_int);

	str_json = cJSON_Print(cJSON_write_str);

end:
	cJSON_Delete(cJSON_write_str);
	return str_json;
}