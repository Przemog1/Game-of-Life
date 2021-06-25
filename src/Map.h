#pragma once
#pragma once
#include "Graphics\Graphics.h"
#include "Graphics\RGBTexture\RGBTexture.h"
#include "Cell.h"

class Map
{
public:
	Map(unsigned int mapSizeX, unsigned int mapSizeY);

	void draw();
	void randomizeCells();

	void calculateNextGeneration();

private:
	void singleCoreCalculation();
	void updateTexture();

private:
	Cell** frontBufferCellArray;
	Cell** backBufferCellArray;

	RGBTexture texture;

	Graphics& graphics;

	const unsigned int mapHeight;
	const unsigned int mapWidth;

	void swapBuffers();
};