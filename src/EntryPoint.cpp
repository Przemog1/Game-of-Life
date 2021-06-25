#include "Application.h"
#include "Game.h"

extern Application* createApplication();

int main()
{
	Application* app = createApplication();
	app->run();
	delete app;
}