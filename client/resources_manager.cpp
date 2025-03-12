#include "resources_manager.h"
#include <iostream>

Mix_Chunk* ResourcesManager::find_audio(const std::string& name)
{
	if (!audio_pool[name])
	{
		std::string error_message = u8"音乐加载失败:\n" + name;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"音乐加载错误", error_message.c_str(), nullptr);
		return nullptr;
	}
	return audio_pool[name];
}

SDL_Texture* ResourcesManager::find_texture(const std::string& name)
{
	if (!texture_pool[name])
	{
		std::string error_message = u8"图片加载失败:\n" + name;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"图片加载错误", error_message.c_str(), nullptr);
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

			main_font = TTF_OpenFont("./resources/main_ttf.TTF", 30);
		}
	}

	{
		uint8_t a_src = 255, r_src = 255, g_src = 111, b_src = 0;
		const Uint32 color_orange = (a_src << 24) | (r_src << 16) | (g_src << 8) | b_src;
		{
			uint8_t a_dst = 255, r_dst = 3, g_dst = 169, b_dst = 244;
			const Uint32 color_blue = (a_dst << 24) | (r_dst << 16) | (g_dst << 8) | b_dst;
			SDL_Texture* player_sit_blue_idle = 
				modify_texture(renderer, texture_pool["player_sit_orange_idle"], color_orange, color_blue);
			texture_pool["player_sit_blue_idle"] = player_sit_blue_idle;
		}
		{
			uint8_t a_dst = 255, r_dst = 232, g_dst = 78, b_dst = 64;
			const Uint32 color_red = (a_dst << 24) | (r_dst << 16) | (g_dst << 8) | b_dst;
			SDL_Texture* player_sit_red_idle = 
				modify_texture(renderer, texture_pool["player_sit_orange_idle"], color_orange, color_red);
			texture_pool["player_sit_red_idle"] = player_sit_red_idle;
		}
		{
			uint8_t a_dst = 255, r_dst = 255, g_dst = 235, b_dst = 59;
			const Uint32 color_yellow = (a_dst << 24) | (r_dst << 16) | (g_dst << 8) | b_dst;
			SDL_Texture* player_sit_yellow_idle =
				modify_texture(renderer, texture_pool["player_sit_orange_idle"], color_orange, color_yellow);
			texture_pool["player_sit_yellow_idle"] = player_sit_yellow_idle;
		}
		{
			uint8_t a_dst = 255, r_dst = 10, g_dst = 143, b_dst = 8;
			const Uint32 color_green = (a_dst << 24) | (r_dst << 16) | (g_dst << 8) | b_dst;
			SDL_Texture* player_sit_green_idle =
				modify_texture(renderer, texture_pool["player_sit_orange_idle"], color_orange, color_green);
			texture_pool["player_sit_green_idle"] = player_sit_green_idle;
		}
		{
			uint8_t a_dst = 255, r_dst = 103, g_dst = 58, b_dst = 183;
			const Uint32 color_purple = (a_dst << 24) | (r_dst << 16) | (g_dst << 8) | b_dst;
			SDL_Texture* player_sit_purple_idle =
				modify_texture(renderer, texture_pool["player_sit_orange_idle"], color_orange, color_purple);
			texture_pool["player_sit_purple_idle"] = player_sit_purple_idle;
		}

	}
}

SDL_Texture* ResourcesManager::modify_texture(SDL_Renderer* renderer, SDL_Texture* tex,
	Uint32 color_src, Uint32 color_dst, int new_width, int new_height)
{
	int width_src, height_src;
	SDL_QueryTexture(tex, NULL, NULL, &width_src, &height_src);

	// 创建目标纹理用于复制原纹理内容
	SDL_Texture* tempTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width_src, height_src);
	if (!tempTexture)
	{
		std::cerr << "Failed to create temporary texture! SDL_Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// 复制原始内容到目标纹理
	SDL_SetRenderTarget(renderer, tempTexture);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);

	// 创建表面并读取目标纹理的像素数据
	SDL_Surface* modifiedSurface = SDL_CreateRGBSurfaceWithFormat(0, width_src, height_src, 32, SDL_PIXELFORMAT_ARGB8888);
	if (!modifiedSurface)
	{
		SDL_DestroyTexture(tempTexture);
		return nullptr;
	}

	// 设置渲染目标并读取像素
	SDL_SetRenderTarget(renderer, tempTexture);
	if (SDL_RenderReadPixels(renderer, NULL, modifiedSurface->format->format, modifiedSurface->pixels, modifiedSurface->pitch) != 0)
	{
		std::cerr << "Failed to read pixels: " << SDL_GetError() << std::endl;
		SDL_FreeSurface(modifiedSurface);
		SDL_DestroyTexture(tempTexture);
		return nullptr;
	}
	SDL_SetRenderTarget(renderer, NULL);

	// 替换颜色
	SDL_LockSurface(modifiedSurface);
	Uint32* pixels = static_cast<Uint32*>(modifiedSurface->pixels);
	for (int i = 0; i < width_src * height_src; ++i)
	{
		if (pixels[i] == color_src)
			pixels[i] = color_dst;
	}
	SDL_UnlockSurface(modifiedSurface);

	SDL_DestroyTexture(tempTexture); // 不再需要临时纹理

	// 处理缩放
	if (new_width <= 0 || new_height <= 0) // 无需缩放
	{
		SDL_Texture* result = SDL_CreateTextureFromSurface(renderer, modifiedSurface);
		SDL_FreeSurface(modifiedSurface);
		return result;
	}

	SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, new_width, new_height, 32, SDL_PIXELFORMAT_ARGB8888);
	SDL_BlitScaled(modifiedSurface, NULL, resizedSurface, NULL);
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, resizedSurface);

	SDL_FreeSurface(modifiedSurface);
	SDL_FreeSurface(resizedSurface);
	return newTexture;
}