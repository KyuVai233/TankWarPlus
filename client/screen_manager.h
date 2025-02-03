#pragma once

#include "manager.h"
#include "screen.h"

#include <string>
#include <unordered_map>

class ScreenManager : public Manager<ScreenManager>
{
	friend class Manager<ScreenManager>;

public:
	//添加界面
	void add_screen(const std::string& screen_id, Screen* screen);

	//跳转界面
	void switch_screen(const std::string& screen_id);

	void on_input(const SDL_Event& event);
	void on_render(SDL_Renderer* renderer);

protected:
	ScreenManager() = default;
	~ScreenManager() = default;

private:
	Screen* currnet_screen = nullptr;
	std::unordered_map<std::string, Screen*> screen_pool;
};
