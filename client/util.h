#pragma once

#include "camera.h"
#include "cjson_write.h"
#include "cjson_parse.h"

#include <SDL.h>
#include <SDL_image.h>

//ÎÞ¹ØÉãÏñ»úÎÆÀíäÖÈ¾
inline void draw(SDL_Renderer* renderer, SDL_Texture* texture,
	const SDL_Rect* rect_src, const SDL_Rect* rect_dst, double angle = 0)
{
	SDL_RenderCopyEx(renderer, texture, rect_src, rect_dst, angle, nullptr, SDL_FLIP_NONE);
}

//¸úËæÉãÏñ»úÎÆÀí»æÖÆ
inline void draw(SDL_Renderer* renderer, Camera* camera, SDL_Texture* texture,
	const SDL_Rect* rect_src, const SDL_Rect* rect_dst, double angle = 0)
{
	SDL_Rect rect_dst_new;
	rect_dst_new.x = camera->get_position().x + rect_dst->x;
	rect_dst_new.y = camera->get_position().y + rect_dst->y;
	rect_dst_new.w = rect_dst->w;
	rect_dst_new.h = rect_dst->h;
	SDL_RenderCopyEx(renderer, texture, rect_src, &rect_dst_new, angle, nullptr, SDL_FLIP_NONE);
}

inline void draw_help(SDL_Renderer* renderer, SDL_Rect* rect)
{
	SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
	SDL_RenderDrawRect(renderer, rect);
}
