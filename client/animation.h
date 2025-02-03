#pragma once

#include "camera.h"
#include "time_timer.h"
#include "vector2.h"
#include "util.h"

#include <functional>
#include <vector>

class Animation
{
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout([&]()
			{
				idx_frame++;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			});
	}

	~Animation() = default;

	void reset()
	{
		timer.restart();
		idx_frame = 0;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_rotation(double angle)
	{
		this->angle = angle;
	}

	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	void set_on_finished(std::function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}

	void add_frame(SDL_Texture* texture, int num_h)
	{
		int width, height;
		SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

		int width_frame = width / num_h;

		for (int i = 0; i <= num_h; i++)
		{
			SDL_Rect rect_src;
			rect_src.x = i * width_frame;
			rect_src.y = 0;
			rect_src.w = width_frame;
			rect_src.h = height;

			frame_list.emplace_back(texture, rect_src);
		}
	}

	void on_update(float detla)
	{
		timer.on_update(detla);
	}

	void on_render(SDL_Renderer* renderer, Camera* camera, Vector2& postion)
	{
		const Frame& frame = frame_list[idx_frame];
		SDL_Rect rect_dst;
		rect_dst.x = postion.x;
		rect_dst.y = position.y;
		rect_dst.w = frame.rect_src.w;
		rect_dst.h = frame.rect_src.h;

		draw(renderer, camera, frame.texture, &frame.rect_src, &rect_dst, angle);
	}

private:
	//帧
	struct Frame
	{
		SDL_Rect rect_src;
		SDL_Texture* texture = nullptr;

		Frame() = default;
		Frame(SDL_Texture* texture, SDL_Rect rect_src)
			:texture(texture), rect_src(rect_src) { }

		~Frame() = default;
	};

private:
	Vector2 position;					//渲染位置
	double angle = 0;					//旋转角度

	TimeTimer timer;					//序列帧定时器
	bool is_loop = true;				//是否循环
	size_t idx_frame = 0;				//序列帧索引
	std::function<void()> on_finished;	//回调
	std::vector<Frame> frame_list;		//帧列表
};
