#include "screen_manager.h"

void ScreenManager::on_entry(const std::string& screen_id)
{
	if (!screen_pool[screen_id])
		return;
	current_screen = screen_pool[screen_id];
	Mix_PlayChannel(-1, current_screen->get_background_bgm(), -1);
}

void ScreenManager::add_screen(const std::string& screen_id, Screen* screen)
{
	screen_pool[screen_id] = screen;
}

void ScreenManager::switch_screen()
{
	if (current_screen->get_next_screen() == "none")
		return;
	const std::string str = current_screen->get_next_screen();
	if (current_screen->get_background_bgm() != screen_pool[str]->get_background_bgm())
	{
		Mix_HaltChannel(-1);
		Mix_PlayChannel(-1, screen_pool[str]->get_background_bgm(), -1);
	}
	current_screen->set_next_screen("none");
	current_screen = screen_pool[str];
	current_screen->entry_screen();
}

void ScreenManager::on_input(const SDL_Event& event)
{
	current_screen->on_input(event);
}

void ScreenManager::on_update(float delta)
{
	current_screen->on_update(delta);
	switch_screen();
	//handle_quit();
}

void ScreenManager::on_render(SDL_Renderer* renderer)
{
	if (!current_screen)	return;
	current_screen->on_render(renderer);
}

void ScreenManager::do_post(float delta)
{
	current_screen->do_post(delta);
}

void ScreenManager::handle_quit()
{
	current_screen->handle_quit();
}