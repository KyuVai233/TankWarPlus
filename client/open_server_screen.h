#pragma once

#include "image.h"
#include "screen.h"
#include "config_home_manager.h"
#include "resources_manager.h"

#include <SDL.h>

#include <ctype.h>
#include <regex>

class OpenServerScreen : public Screen
{
public:
	OpenServerScreen(const std::string& screen_type, Mix_Chunk* background_bgm);

	~OpenServerScreen() = default;

	void on_input(const SDL_Event& event) override;

	void on_update(float delta) override;

	void on_render(SDL_Renderer* renderer) override;

	void connect();

private:
	bool is_try_build = false;		//�Ƿ��Դ�������
	bool is_try_join = false;		//�Ƿ��Լ��뷿��

	std::string str_ip;				//����ip�ַ���
	std::string str_port;			//����˿��ַ���

	bool is_write_ip = false;		//�Ƿ�ʼ����ip
	bool is_write_port = false;		//�Ƿ�ʼ����˿�

	Button* button_ip = nullptr;
	Button* button_port = nullptr;
};
