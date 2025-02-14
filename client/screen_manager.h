#pragma once

#include "manager.h"
#include "screen.h"

#include <string>
#include <unordered_map>

class ScreenManager : public Manager<ScreenManager>
{
	friend class Manager<ScreenManager>;

public:
	//���ÿ�ʼ����
	void on_entry(const std::string& screen_id);

	//��ӽ���
	void add_screen(const std::string& screen_id, Screen* screen);

	//��ת����
	void switch_screen();

	void on_input(const SDL_Event& event);
	void on_update(float delta);
	void on_render(SDL_Renderer* renderer);
	void to_post();
	void do_post(float delta);
	void handle_quit();

protected:
	ScreenManager() = default;

	~ScreenManager() = default;

private:
	Screen* current_screen = nullptr;
	std::unordered_map<std::string, Screen*> screen_pool;
};
