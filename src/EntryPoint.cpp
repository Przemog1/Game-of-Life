#include "Application/Application.h"
#include "Game\Game.h"

extern Application* createApplication();

int main()
{
	Application* app = createApplication();
	app->run();
	delete app;
}