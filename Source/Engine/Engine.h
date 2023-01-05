#pragma once

#include <iostream>

class Engine {
public:
	static Engine& GetInstance();

	void Run();

private:
	Engine();
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
};
