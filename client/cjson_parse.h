#pragma once

#include <cJSON.h>

#include <string>

//解析"/get_player_list" json，参数赋值
inline bool parse_get_player_list(const std::string& str_player, std::string player_id, int identity)
{
	cJSON* parse_player = cJSON_Parse(str_player.c_str());
	cJSON* cJSON_player_id;
	cJSON* cJSON_identity;
	if (!parse_player)
		goto end;

	cJSON_player_id = cJSON_GetObjectItemCaseSensitive(parse_player, "player_id");
	if (cJSON_IsString(cJSON_player_id) || !cJSON_player_id->valuestring)
		goto end;
	player_id = cJSON_player_id->valuestring;

	cJSON_identity = cJSON_GetObjectItemCaseSensitive(parse_player, "identity");
	if (cJSON_IsNumber(cJSON_identity))
		goto end;
	identity = cJSON_player_id->valueint;
	cJSON_Delete(parse_player);
	return true;

end:
	cJSON_Delete(parse_player);
	return false;
}