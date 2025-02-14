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
					button->set_is_click_left(true);
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->set_is_click_right(true);
			}
		}
		break;
	default:
		break;
	}
}

void Screen::on_update(float delta)
{
	for (Button* button : button_list)
	{
		if (button->get_is_clicked_left())
		{
			Mix_PlayChannel(-1, button->get_music_clicked(), 0);
			button->take_on_left_clicked();
		}
		else if (button->get_is_clicked_right())
		{
			Mix_PlayChannel(-1, button->get_music_clicked(), 0);
			button->take_on_right_clicked();
		}
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

void Screen::to_post()
{

}

void Screen::do_post(float delta)
{

}

void Screen::handle_quit()
{

}