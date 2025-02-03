#pragma once

#include "status_node.h"

#include <string>
#include <unordered_map>

class StatusMachine
{
public:
	StatusMachine() = default;
	~StatusMachine() = default;

public:
	void on_update(float delta);
	
	//进入状态
	void set_entry(const std::string& id);

	//改变状态
	void switch_status(const std::string& id);

	//注册状态
	void register_status(const std::string& id, StatusNode* status_node);

private:
	bool need_init = true;										//是否需要初始化最开始节点
	StatusNode* current_status = nullptr;						//当前状态节点
	std::unordered_map<std::string, StatusNode*> status_pool;	//状态池
};
