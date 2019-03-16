#include "Map.h"
#include "..\..\Graphics\Graphics.h"
//#include <memory>

#include<time.h>
#include <cstdlib>
#include <iostream>


Map::Map(unsigned int mapSizeX, unsigned int mapSizeY)
	:texture(mapSizeX, mapSizeY),
	graphics(*Graphics::getGraphics()),
	mapHeight(mapSizeY),
	mapWidth(mapSizeX)
{
	frontBufferCellArray = new Cell*[mapSizeY];

	for (unsigned int i = 0; i < mapSizeY; i++)
		frontBufferCellArray[i] = new Cell[mapSizeX];

	backBufferCellArray = new Cell*[mapSizeY];

	for (unsigned int i = 0; i < mapSizeY; i++)
		backBufferCellArray[i] = new Cell[mapSizeX];
}

void Map::swapBuffers()
{
	std::swap<Cell**>(frontBufferCellArray, backBufferCellArray);
}

//TODO: width and height variables
void Map::randomizeCells()
{
	srand((unsigned int)time(NULL));

	for (unsigned int i = 1; i < mapHeight - 1; i++)
	{
		for (unsigned int j = 1; j < mapWidth - 1; j++)
		{
			if (rand() % 5)
				frontBufferCellArray[i][j].setState(true);
			else
				frontBufferCellArray[i][j].setState(false);
		}
	}
}

void Map::updateTexture()
{
	for (unsigned int i = 1; i < mapHeight - 1; i++)
		for (unsigned int j = 1; j < mapWidth - 1; j++)
		{
			if (frontBufferCellArray[i][j].isAlive())
				texture.getPixel(i, j) = Cell::getAliveCellColor();
			else
				texture.getPixel(i, j) = Cell::getDeadCellColor();
		}

	texture.update();
}

void Map::draw()
{
	updateTexture();
	graphics.draw(texture);
	swapBuffers();
}

void Map::calculateNextGeneration()
{
	singleCoreCalculation();
}

void Map::singleCoreCalculation()
{
	for (unsigned int i = 1; i < mapHeight - 1; i++)
	{
		for (unsigned int j = 1; j < mapWidth - 1; j ++)
		{
			unsigned int counter = 0;

			counter =
				frontBufferCellArray[i - 1][j - 1].isAlive() +
				frontBufferCellArray[i - 1][j].isAlive() +
				frontBufferCellArray[i - 1][j + 1].isAlive() +

				frontBufferCellArray[i][j - 1].isAlive() +
				frontBufferCellArray[i][j + 1].isAlive() +

				frontBufferCellArray[i + 1][j - 1].isAlive() +
				frontBufferCellArray[i + 1][j].isAlive() +
				frontBufferCellArray[i + 1][j + 1].isAlive();

			if (frontBufferCellArray[i][j].isAlive())
			{
				if (counter != 2 && counter != 3)
					backBufferCellArray[i][j].setState(false);
				else
					backBufferCellArray[i][j].setState(true);
			}
			else
			{
				if (counter == 3)
					backBufferCellArray[i][j].setState(true);
				else
					backBufferCellArray[i][j].setState(false);
			}
		}
	}
}