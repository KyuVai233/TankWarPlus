#pragma once

#include "manager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <filesystem>
#include <unordered_map>
#include <string>

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	//加载资源
	void load(SDL_Renderer* renderer);

	Mix_Chunk* find_audio(const std::string& name);
	SDL_Texture* find_texture(const std::string& name);
	TTF_Font* get_main_font() const
	{
		return main_font;
	}

protected:
	ResourcesManager() = default;
	~ResourcesManager() = default;

private:
	std::unordered_map<std::string, Mix_Chunk*> audio_pool;
	std::unordered_map<std::string, SDL_Texture*> texture_pool;

	TTF_Font* main_font = nullptr;

private:
	//更改纹理中某个颜色至另一个颜色且调整其大小
	SDL_Texture* modify_texture(SDL_Renderer* renderer, SDL_Texture* tex,
		Uint32 color_src, Uint32 color_dst, int new_width = 0, int new_height = 0);

};
