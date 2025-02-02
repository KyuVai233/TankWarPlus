#include "screen_manager.h"

void ScreenManager::add_screen(Screen* screen)
{
	screen_list.emplace_back(screen);
}

void ScreenManager::switch_screen(const ScreenType& screen_type)
{
	for (Screen* screen : screen_list)
	{
		if (screen->get_screen_type() == screen_type)
		{
			currnet_screen = screen;
			return;
		}
	}
}