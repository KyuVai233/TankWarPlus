#include "resources_manager.h"

Mix_Chunk* ResourcesManager::find_audio(const std::string& name)
{
	if (!audio_pool[name])
	{
		std::string error_message = u8"“Ù¿÷º”‘ÿ ß∞‹:\n" + name;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"“Ù¿÷º”‘ÿ¥ÌŒÛ", error_message.c_str(), nullptr);
		return nullptr;
	}
	return audio_pool[name];
}

SDL_Texture* ResourcesManager::find_texture(const std::string& name)
{
	if (!texture_pool[name])
	{
		std::string error_message = u8"Õº∆¨º”‘ÿ ß∞‹:\n" + name;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"Õº∆¨º”‘ÿ¥ÌŒÛ", error_message.c_str(), nullptr);
		return nullptr;
	}
	return texture_pool[name];
}

void ResourcesManager::load(SDL_Renderer* renderer)
{
	using namespace std::filesystem;

	for (const auto& entry : directory_iterator("resources"))
	{
		if (entry.is_regular_file())
		{
			const path& path = entry.path();
			if (path.extension() == ".png")
			{
				SDL_Texture* texture = IMG_LoadTexture(renderer, path.u8string().c_str());
				texture_pool[path.stem().u8string()] = texture;
			}
			else if (path.extension() == ".mp3")
			{
				Mix_Chunk* audio = Mix_LoadWAV(path.u8string().c_str());
				audio_pool[path.stem().u8string()] = audio;
			}
		}
	}
}