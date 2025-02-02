#pragma once

#include "manager.h"
#include "screen.h"

#include <vector>

class ScreenManager : public Manager<ScreenManager>
{
	friend class Manager<ScreenManager>;

public:
	//添加界面
	void add_screen(Screen* screen);

	//跳转界面
	void switch_screen(const ScreenType& screen_type);

	void on_input(const SDL_Event& event);
	void on_render(SDL_Renderer* renderer);

protected:
	ScreenManager() = default;
	~ScreenManager() = default;

private:
	Screen* currnet_screen = nullptr;
	std::vector<Screen*> screen_list;
};
