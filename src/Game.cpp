#include "Game.h"
#include "Graphics\Graphics.h"
#include <iostream>

void Game::update()
{
	map.calculateNextGeneration();
	map.draw();
}

void Game::initialize()
{
	map.randomizeCells();
}

Game::Game(const std::string& title, unsigned int width, unsigned int height)
	:Application(title, width, height), 
	graphics(*Graphics::getGraphics()),
	map(width, height)
{

}

Application* createApplication()
{
	return new Game("Hello!", 1920, 1080);
}
