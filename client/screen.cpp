#include "screen.h"

void Screen::on_input(const SDL_Event& event)
{
	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y))
			{
				if (event.button.button == SDL_BUTTON_LEFT)
					button->take_on_left_clicked();
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->take_on_right_clicked();
			}
		}
		break;
	default:
		break;
	}
}

void Screen::on_render(SDL_Renderer* renderer)
{
	if (!tex_background)	return;
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