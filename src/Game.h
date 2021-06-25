#pragma once
#include "Application.h"
#include "Graphics\Graphics.h"
#include "Map.h"

class Game : public Application
{
public:
	Game(const std::string& title, unsigned int width, unsigned int height);

private:
	void initialize() override;
	void update() override;

	Graphics& graphics;
	Map map;
};
