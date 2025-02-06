#pragma once

#include "screen.h"

class OpenServerScreen : public Screen
{
public:
	OpenServerScreen(SDL_Texture* tex_background, const std::string& screen_type)
		:Screen(tex_background, screen_type)
	{
	}

	~OpenServerScreen()
	{
	}

private:

};
