#pragma once

#include "screen.h"
#include "config_home_manager.h"
#include "util.h"

#include <mutex>

class HomeScreen : public Screen
{
public:
	HomeScreen(const std::string& screen_type, Mix_Chunk* background_bgm);

	~HomeScreen() = default;

	void on_update(float delta) override;

	void do_post(float delta) override;

	void handle_quit() override;

private:
	bool is_bulit = false;
	std::mutex mutex_join_or_switch;
	std::mutex mutex_get_player_list;
};
