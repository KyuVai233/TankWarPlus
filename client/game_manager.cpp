#include "game_manager.h"

int GameManager::run(int argc, char** argv)
{
	if (ConfigGameManager::instance()->get_player()->get_identity() 
		== Player::Identity::Owner)
	{
		std::thread thread_on_server(&GameManager::on_server, this, delta);

		//join
	}

	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_game_quit)
	{
		while (SDL_PollEvent(&event))
		{
			on_input(event);
		}

		Uint64 current_counter = SDL_GetPerformanceCounter();
		delta = (float)(current_counter - last_counter) / counter_freq;
		last_counter = current_counter;
		if (delta * 1000 < 1000.0 / 60)
			SDL_Delay((Uint32)(1000.0 / 60 - delta * 1000));

		on_update(delta);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		on_render(renderer);

		SDL_RenderPresent(renderer);
	}

	return 0;
}

void GameManager::on_server(float delta)
{
	do_post(delta);

	ConfigGameManager::instance()->server.listen(ConfigHomeManager::instance()->get_ip(),
		ConfigHomeManager::instance()->get_port());

	//listen
}

void GameManager::on_input(const SDL_Event& event)
{
	ScreenManager::instance()->on_input(event);
}

void GameManager::on_update(float delta)
{
	ConfigHomeManager::instance()->on_update(delta);
	ScreenManager::instance()->on_update(delta);
}

void GameManager::on_render(SDL_Renderer* renderer)
{
	ScreenManager::instance()->on_render(renderer);
}

void GameManager::do_post(float delta)
{
	ScreenManager::instance()->do_post(delta);
}


GameManager::GameManager()
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image 初始化失败");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败！");
	init_assert(!TTF_Init(), u8"SDL_ttf 初始化失败");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	window = SDL_CreateWindow(u8"小学生tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
	init_assert(window, u8"window 初始化失败");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"renderer 初始化失败");

	ResourcesManager::instance()->load(renderer);

	ScreenManager::instance()->add_screen("main_screen", new MainScreen(ResourcesManager::instance()->find_texture("main_background"), "main_screen"));
	ScreenManager::instance()->add_screen("open_server_screen", new OpenServerScreen(ResourcesManager::instance()->find_texture("open_server_background"), "open_server_screen"));
	ScreenManager::instance()->on_entry("main_screen");
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void GameManager::init_assert(bool flag, const char* err_msg)
{
	if (flag)	return;

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
	exit(-1);
}