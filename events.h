#pragma once

class c_events {
public:
	virtual void post(void *sender, const char *msg);
};