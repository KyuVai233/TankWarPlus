#include "screen.h"

void Screen::on_input(const SDL_Event& event)
{
	for (Button* button : button_list)
		button->on_input(event);
}

void Screen::on_render(SDL_Renderer* renderer)
{
	int width, height;
	SDL_QueryTexture(tex_background, nullptr, nullptr, &width, &height);
	SDL_Rect rect =
	{
		0, 0,
		width, height
	};

	draw(renderer, tex_background, &rect, &rect);

	for (Button* button : button_list)
		button->on_render(renderer);
}