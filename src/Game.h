#pragma once

#include "Application.h"
#include "Graphics\Graphics.h"
#include "Map.h"
#include "IGenerationCalculator.h"
#include <memory>

class Game : public Application
{
public:
	enum class EGenerationCalculatorType
	{
		SINGLE_THREAD,
		MULTIPLE_THREADS
	};

public:
	Game(const std::string& title, unsigned int width, unsigned int height, EGenerationCalculatorType egct);

private:
	void initialize() override;
	void update() override;
	unsigned int texture;

	Graphics& graphics;

	Map map;
	std::unique_ptr<IGenerationCalculator> generationCalculator;
};
