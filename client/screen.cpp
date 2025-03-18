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
			else if(!button->check_in_button(pos_cursor.x, pos_cursor.y)
				&& button->get_button_status() == Button::ButtonStatus::Covered)
				button->set_button_status(Button::ButtonStatus::Idle);
		}
		break;
	default:
		break;
	}

	for (Slider* slider : slider_list)
	{
		slider->on_input(event);
	}

	for (SecondScreen* screen : second_screen_list)
	{
		screen->on_input(event);
	}
}

void Screen::on_update(float delta)
{
	for (Button* button : button_list)
	{
		button->on_update(delta);
	}

	for (SecondScreen* screen : second_screen_list)
	{
		screen->on_update(delta);
	}
}

void Screen::on_render(SDL_Renderer* renderer)
{
	for (Image* img : image_list)
		img->draw_image(renderer);

	for (Button* button : button_list)
	{
		button->on_render(renderer); 
		draw_help(renderer, button->get_rect_usable());
	}

	for (Slider* slider : slider_list)
	{
		slider->on_render(renderer);
	}

	for (SecondScreen* screen : second_screen_list)
	{
		screen->on_render(renderer);
	}
}

void Screen::do_post(float delta)
{
	for (SecondScreen* screen : second_screen_list)
	{
		screen->do_post(delta);
	}
}

void Screen::handle_quit()
{

}

void Screen::entry_screen()
{
	for (Button* button : button_list)
	{
		button->set_button_status(Button::ButtonStatus::Idle);
	}

	for (SecondScreen* screen : second_screen_list)
	{
		screen->entry_screen();
	}
}