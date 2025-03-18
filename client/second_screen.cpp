#include "second_screen.h"

void SecondScreen::on_input(const SDL_Event& event)
{
	SDL_Point pos_cursor = { event.motion.x,event.motion.y };
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
		for (Button* button : button_list)
		{
			if (button->check_in_button(pos_cursor.x, pos_cursor.y))
			{
				button->set_button_status(Button::ButtonStatus::Clicked);
				if (event.button.button == SDL_BUTTON_LEFT)
					button->take_on_left_clicked();
				else if (event.button.button == SDL_BUTTON_RIGHT)
					button->take_on_right_clicked();
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
			else if (!button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Covered)
				button->set_button_status(Button::ButtonStatus::Idle);
		}
		break;
	default:
		break;
	}

	for (Slider* slider : slider_list)
		slider->on_input(event);
}

void SecondScreen::on_update(float delta)
{
	for (Button* button : button_list)
	{
		button->on_update(delta);
	}
}

void SecondScreen::on_render(SDL_Renderer* renderer)
{
	for (Image* img : image_list)
		img->draw_image(renderer);

	for (Button* button : button_list)
	{
		button->on_render(renderer);
		draw_help(renderer, button->get_rect_usable());
	}

	for (Slider* slider : slider_list)
		slider->on_render(renderer);
}

void SecondScreen::do_post(float delta)
{

}

void SecondScreen::entry_screen()
{
	for (Button* button : button_list)
	{
		button->set_button_status(Button::ButtonStatus::Idle);
	}
}

void SecondScreen::set_button(Button* button)
{
	button_list.emplace_back(button);
}

void SecondScreen::set_image(Image* image)
{
	image_list.emplace_back(image);
}