#include "Game.h"
#include "Graphics\Graphics.h"
#include <iostream>
#include "SingleCoreGenerationCalculator.h"

Game::Game(const std::string& title, unsigned int windowWidth, unsigned int windowHeight)
	:Application(title, windowWidth, windowHeight),
	map(windowWidth, windowHeight),
	graphics(*Graphics::getGraphics())
{
	generationCalculator = std::make_unique<SingleCoreGenerationCalculator>();
}

void Game::initialize()
{
	map.randomizeCells();
}

void Game::update()
{
	generationCalculator->calculateNextGeneration(map);
	map.draw();
}
