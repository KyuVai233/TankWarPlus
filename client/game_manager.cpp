#include "game_manager.h"

int GameManager::run(int argc, char** argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	const Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_game_quit)
	{
		ConfigGameManager* con_game_instance = ConfigGameManager::instance();
		if (con_game_instance->get_player()->get_identity()
			== Player::Identity::Owner && !con_game_instance->get_is_on_server())
		{
			con_game_instance->open_server();
			std::thread thread_on_server(&GameManager::on_server, this, delta);

			thread_on_server.detach();
		}

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
}

void GameManager::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_QUIT:
		is_game_quit = true;
		break;
	default:
		break;
	}

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
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 ��ʼ��ʧ��");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image ��ʼ��ʧ��");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer ��ʼ��ʧ�ܣ�");
	init_assert(!TTF_Init(), u8"SDL_ttf ��ʼ��ʧ��");

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");

	window = SDL_CreateWindow(u8"Сѧ��tank", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_SHOWN);
	init_assert(window, u8"window ��ʼ��ʧ��");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(renderer, u8"renderer ��ʼ��ʧ��");

	ResourcesManager* res_instance = ResourcesManager::instance();
	res_instance->load(renderer);

	ScreenManager* scr_instance = ScreenManager::instance();
	scr_instance->add_screen("main_screen",new MainScreen("main_screen", res_instance->find_audio("main_bgm")));
	scr_instance->add_screen("open_server_screen",new OpenServerScreen("open_server_screen", res_instance->find_audio("main_bgm")));
	scr_instance->add_screen("home_screen",new HomeScreen("home_screen", res_instance->find_audio("main_bgm")));
	scr_instance->add_screen("config_game_screen",new ConfigGameScreen("config_game_screen", res_instance->find_audio("main_bgm")));
	scr_instance->on_entry("main_screen");
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

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"��Ϸ����ʧ��", err_msg, window);
	exit(-1);
}