#pragma once

#include <cJSON.h>

#include <string>

//±‡–¥"/get_player_list" cJSON
inline const std::string& write_get_player_list(const std::string& player_id, int identity)
{
	std::string str_player;
	cJSON* cJSON_player = cJSON_CreateObject();
	cJSON* cJSON_player_id;
	cJSON* cJSON_identity;
	if (!cJSON_player)
		goto end;

	cJSON_player_id = cJSON_CreateString(player_id.c_str());
	if (!cJSON_player_id)
		goto end;
	cJSON_AddItemToObject(cJSON_player, "player_id", cJSON_player_id);

	cJSON_identity = cJSON_CreateNumber(identity);
	if (!cJSON_identity)
		goto end;
	cJSON_AddItemToObject(cJSON_player, "identity", cJSON_identity);

	str_player = cJSON_Print(cJSON_player);

end:
	cJSON_Delete(cJSON_player);
	return str_player;
}