#include "SingleCoreGenerationCalculator.h"

void SingleCoreGenerationCalculator::calculateNextGeneration(Map& map)
{
	const unsigned int mapHeight = map.getMapHeight();
	const unsigned int mapWidth = map.getMapWidth();
	Cell** frontBufferCellArray = map.getFrontBuffer();
	Cell** backBufferCellArray = map.getBackBuffer();

	for (unsigned int i = 1; i < mapHeight - 1; i++)
	{
		for (unsigned int j = 1; j < mapWidth - 1; j++)
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
