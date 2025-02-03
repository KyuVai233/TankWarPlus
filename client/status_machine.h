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
	
	//����״̬
	void set_entry(const std::string& id);

	//�ı�״̬
	void switch_status(const std::string& id);

	//ע��״̬
	void register_status(const std::string& id, StatusNode* status_node);

private:
	bool need_init = true;										//�Ƿ���Ҫ��ʼ���ʼ�ڵ�
	StatusNode* current_status = nullptr;						//��ǰ״̬�ڵ�
	std::unordered_map<std::string, StatusNode*> status_pool;	//״̬��
};
