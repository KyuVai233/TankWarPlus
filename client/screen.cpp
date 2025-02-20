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
					button->set_button_status(Button::ButtonStatus::ClickedLeft);
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->set_button_status(Button::ButtonStatus::ClickedRight);
			}
		}
		break;
	case SDL_MOUSEMOTION:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Idle)
			{
				button->set_button_status(Button::ButtonStatus::Covered);
				Mix_PlayChannel(-1, button->get_music_covered(), 0);
			}
			else if(!button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Covered)
				button->set_button_status(Button::ButtonStatus::Idle);
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
		button->on_update(delta);
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

void Screen::do_post(float delta)
{

}

void Screen::handle_quit()
{

}