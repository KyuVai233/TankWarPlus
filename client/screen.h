#pragma once

#include "button.h"
#include "image.h"
#include "second_screen.h"

#include "../thirdparty/httplib.h"

#include <vector>
#include <string>
#include <unordered_map>

class Screen
{
public:
	Screen() = delete;
	Screen(const std::string& screen_type, Mix_Chunk* background_bgm)
		:screen_type(screen_type), 
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

	//进入界面设置
	virtual void entry_screen();

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

	std::vector<Button*> button_list;									//按钮列表
	std::vector<Image*> image_list;										//图片列表
	std::unordered_map<std::string, SecondScreen*> second_screen_pool;	//存在的副屏池
	std::vector<SecondScreen*> second_screen_list;						//当前副屏列表
};