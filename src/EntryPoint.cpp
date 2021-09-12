#include "Application.h"
#include "Game.h"

extern Application* createApplication();

int main()
{
	Application* app = new Game("Hello", 1920, 1080, Game::EGenerationCalculatorType::MULTIPLE_THREADS);
	//Application* app = new Game("Hello", 1920, 1080, Game::EGenerationCalculatorType::SINGLE_THREAD);
	app->run();
	delete app;
}