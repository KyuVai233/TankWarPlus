#pragma once

#include "vector2.h"
#include "util.h"

#include <SDL.h>
#include <SDL_image.h>

class Image
{
public:
	Image(SDL_Texture* texture, SDL_Rect rect_src, SDL_Rect rect_dst)
		: texture(texture), rect_src(rect_src), rect_dst(rect_dst)
	{
	}

	~Image() = default;

	void draw_image(SDL_Renderer* renderer)
	{
		draw(renderer, texture, &rect_src, &rect_dst);
	}

private:
	SDL_Texture* texture = nullptr;
	SDL_Rect rect_src;
	SDL_Rect rect_dst;
};
