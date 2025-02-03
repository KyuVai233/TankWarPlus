#pragma once

#include "manager.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <filesystem>
#include <unordered_map>
#include <string>

class ResourcesManager : public Manager<ResourcesManager>
{
	friend class Manager<ResourcesManager>;

public:
	//������Դ
	void load(SDL_Renderer* renderer);

	Mix_Chunk* find_audio(const std::string& name)
	{
		if (!audio_pool[name])
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"���ּ��ش���", name.c_str(), nullptr);
			return nullptr;
		}
		return audio_pool[name];
	}

	SDL_Texture* find_texture(const std::string& name)
	{
		if (!texture_pool[name])
		{
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"ͼƬ���ش���", name.c_str(), nullptr);
			return nullptr;
		}
		return texture_pool[name];
	}

protected:
	ResourcesManager() = default;
	~ResourcesManager() = default;

private:
	std::unordered_map<std::string, Mix_Chunk*> audio_pool;
	std::unordered_map<std::string, SDL_Texture*> texture_pool;
};
