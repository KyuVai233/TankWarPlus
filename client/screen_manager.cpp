#include "screen_manager.h"

void ScreenManager::add_screen(const std::string& screen_id, Screen* screen)
{
	screen_pool[screen_id] = screen;
}

void ScreenManager::switch_screen(const std::string& screen_id)
{
	currnet_screen = screen_pool[screen_id];
}

void ScreenManager::on_input(const SDL_Event& event)
{
	currnet_screen->on_input(event);
}

void ScreenManager::on_render(SDL_Renderer* renderer)
{
	currnet_screen->on_render(renderer);
}