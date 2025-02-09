#include "open_server_screen.h"

void OpenServerScreen::on_input(const SDL_Event& event)
{

}

void OpenServerScreen::on_render(SDL_Renderer* renderer)
{

}

void OpenServerScreen::to_post()
{
	ConfigGameManager* instance = ConfigGameManager::instance();
	const std::string str_address = ConfigHomeManager::instance()->get_address();
	instance->client = new httplib::Client(str_address);
	instance->client->set_keep_alive(true);

	httplib::Result result_join = instance->client->Post("join", 
		instance->get_player()->get_player_id(), "text/plain");
	if (!result_join || result_join != 200)
	{
		//δ���ӵ�������
		return;
	}
	
	int order = std::stoi(result_join->body);
	if (order == -1)
	{
		//����δ����
		return;
	}
}