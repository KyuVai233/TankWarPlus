#pragma once

class StatusNode
{
public:
	StatusNode() = default;
	~StatusNode() = default;

	virtual void on_enter() { }
	virtual void on_update(float delta) { }
	virtual void on_exit() { }

private:

};
