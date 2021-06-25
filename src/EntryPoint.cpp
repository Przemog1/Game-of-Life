#include "Application.h"
#include "Game.h"

extern Application* createApplication();

int main()
{
	Application* app = new Game("Hello", 1920, 1080);
	app->run();
	delete app;
}