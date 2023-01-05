#include "../Engine.h"

Engine& Engine::GetInstance() {
	static Engine engine;

	return engine;
}

void Engine::Run() {
	std::cout << "Hello" << std::endl;
}

Engine::Engine() {
	//
}
