#pragma once

#include <cJSON.h>

#include <string>

//½âÎöstr+int
inline bool parse_cJSON_string_and_int(const std::string& str_json, std::string str, int num_int)
{
	cJSON* cJSON_parse_str = cJSON_Parse(str_json.c_str());
	cJSON* cJSON_str;
	cJSON* cJSON_num_int;
	if (!cJSON_parse_str)
		goto end;

	cJSON_str = cJSON_GetObjectItemCaseSensitive(cJSON_parse_str, "str");
	if (cJSON_IsString(cJSON_str) || !cJSON_str->valuestring)
		goto end;
	str = cJSON_str->valuestring;

	cJSON_num_int = cJSON_GetObjectItemCaseSensitive(cJSON_parse_str, "num_int");
	if (cJSON_IsNumber(cJSON_num_int))
		goto end;
	num_int = cJSON_str->valueint;
	cJSON_Delete(cJSON_parse_str);
	return true;

end:
	cJSON_Delete(cJSON_parse_str);
	return false;
}