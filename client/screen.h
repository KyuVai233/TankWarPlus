#pragma once

#include "button.h"

#include "../thirdparty/httplib.h"

#include <vector>
#include <string>

class Screen
{
public:
	Screen() = delete;
	Screen(SDL_Texture* tex_background, const std::string& screen_type, Mix_Chunk* background_bgm)
		:tex_background(tex_background), screen_type(screen_type), 
		next_screen("none"), background_bgm(background_bgm) { };
	~Screen() = default;

	void set_next_screen(const std::string& next_screen)
	{
		this->next_screen = next_screen;
	}

	const std::string& get_next_screen() const
	{
		return next_screen;
	}

	Mix_Chunk* get_background_bgm() const
	{
		return background_bgm;
	}

	virtual void on_input(const SDL_Event& event);
	virtual void on_update(float delta);
	virtual void on_render(SDL_Renderer* renderer);
	virtual void do_post(float delta);
	//处理玩家掉线和退出
	virtual void handle_quit();

protected:
	std::string screen_type;
	std::string next_screen;
	Mix_Chunk* background_bgm;

	std::vector<Button*> button_list;				//按钮列表
	SDL_Texture* tex_background = nullptr;			//背景图
};