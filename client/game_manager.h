#pragma once

#include "included_manager.h"
#include "included_screen.h"
#include "player.h"
#include "util.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <thread>

class GameManager : public Manager<GameManager>
{
	friend class Manager<GameManager>;

public:
	int run(int argc, char** argv);

protected:
	GameManager();
	~GameManager();

private:
	SDL_Event event;
	bool is_game_quit = false;							//��Ϸ�Ƿ��˳�

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	float delta = 0;

private:
	//��ʼ����ʶ
	void init_assert(bool flag, const char* err_msg);

	void on_server(float delta);

	void on_input(const SDL_Event& event);

	void on_update(float delta);

	void on_render(SDL_Renderer* renderer);

	void do_post(float delta);

};