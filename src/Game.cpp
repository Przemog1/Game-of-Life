#include "Game.h"
#include "Graphics\Graphics.h"
#include <iostream>
#include "SingleCoreGenerationCalculator.h"
#include "MTGenerationCalculator.h"
#include <assert.h>
#include <thread>

Game::Game(const std::string& title, unsigned int windowWidth, unsigned int windowHeight, EGenerationCalculatorType egct)
	:Application(title, windowWidth, windowHeight),
	map(windowWidth, windowHeight),
	graphics(*Graphics::getGraphics())
{
	const unsigned int threadCnt = std::thread::hardware_concurrency();
	switch (egct)
	{
	case EGenerationCalculatorType::SINGLE_THREAD:
		generationCalculator = std::make_unique<SingleCoreGenerationCalculator>();
		break;
	case EGenerationCalculatorType::MULTIPLE_THREADS:


		generationCalculator = std::make_unique<MTGenerationCalculator>(threadCnt);
		break;
	default:
		assert(false);
	}
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
