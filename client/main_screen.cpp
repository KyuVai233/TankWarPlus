#include "main_screen.h"

void MainScreen::on_input(const SDL_Event& event)
{
	Screen::on_input(event);
}

void MainScreen::on_update(float delta)
{
	Screen::on_update(delta);
}

void MainScreen::on_render(SDL_Renderer* renderer)
{
	Screen::on_render(renderer);

	logo->draw_image(renderer);
}