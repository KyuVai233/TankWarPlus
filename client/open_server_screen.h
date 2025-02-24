#pragma once

#include "image.h"
#include "screen.h"
#include "config_home_manager.h"
#include "resources_manager.h"

#include <SDL.h>

#include <ctype.h>
#include <regex>

class OpenServerScreen : public Screen
{
public:
	OpenServerScreen(const std::string& screen_type, Mix_Chunk* background_bgm);

	~OpenServerScreen() = default;

	void on_input(const SDL_Event& event) override;

	void on_update(float delta) override;

	void on_render(SDL_Renderer* renderer) override;

	void connect();

private:
	bool is_try_build = false;		//是否尝试创建房间
	bool is_try_join = false;		//是否尝试加入房间

	std::string str_ip;				//输入ip字符串
	std::string str_port;			//输入端口字符串

	bool is_write_ip = false;		//是否开始输入ip
	bool is_write_port = false;		//是否开始输入端口

	Button* button_ip = nullptr;
	Button* button_port = nullptr;
};
