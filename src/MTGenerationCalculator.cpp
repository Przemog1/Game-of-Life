#include "MTGenerationCalculator.h"
#include <algorithm>

#include <iostream>

MTGenerationCalculator::MTGenerationCalculator(unsigned int numberOfThreads)
	: shouldCloseFlag(false), dataReadyToProcessFlag(false), currentStateBitflag(0u), currentWorkStateBitflag(0u)
{
	if (numberOfThreads == 0)
		numberOfThreads = 1;
	if (numberOfThreads > MAX_THREADS)
		numberOfThreads = MAX_THREADS;

	threadCnt = numberOfThreads -= 1; // first instance will be running on this thread

	for (std::uint16_t i = 0u; i < threadCnt; i++)
		allThreadsWaitingBitflag |= (0x1u << i);
	allThreadsFinishedBitflag = allThreadsWaitingBitflag;

	// start all threads
	threads.reserve(numberOfThreads);
	for (int i = 1; i < threadCnt + 1; i++)
	{
		std::thread thread = std::thread(&MTGenerationCalculator::concurrentFunction, this, i);
		threads.push_back(std::move(thread));
	}
}

MTGenerationCalculator::~MTGenerationCalculator()
{
	waitInMainThreadForAllThreadsToBeReady();
	shouldCloseFlag = true;
	{
		std::unique_lock lck(dataReadyToProcessLock);
		currentStateBitflag = allThreadsCalculatingBitflag;
	}
	dataReadyToProcess.notify_all();

	for (auto& thread : threads)
		thread.join();
}

void MTGenerationCalculator::calculateNextGeneration(Map& map)
{
	mapPtr = &map;

	waitInMainThreadForAllThreadsToBeReady();
	{
		std::unique_lock lck(dataReadyToProcessLock);
		currentStateBitflag = allThreadsCalculatingBitflag;
		currentWorkStateBitflag = allThreadsCalculatingBitflag;
	}
	dataReadyToProcess.notify_all();

	calculateNextGeneration_impl(0u);

	waitInMainThreadForAllThreadsToBeReady();
}

void MTGenerationCalculator::concurrentFunction(unsigned int threadSystemID)
{
	const std::uint16_t thisThreadStateBitflag = 0x1u << (threadSystemID - 1u);

	while (true)
	{
		std::unique_lock lckRdy(dataReadyToProcessLock);
		currentStateBitflag |= thisThreadStateBitflag;
		if (currentStateBitflag == allThreadsWaitingBitflag)
			allThreadsAreWaiting.notify_one();
		dataReadyToProcess.wait(lckRdy, [&]() { return currentStateBitflag == allThreadsCalculatingBitflag; });
		lckRdy.unlock();

		if (shouldCloseFlag)
		{
			std::cout << threadSystemID << std::endl;
			return;
		}

		calculateNextGeneration_impl(threadSystemID);

		// TODO: make sure if 2 condition variables are neccessary
		std::unique_lock lckFin(allThreadsFinishedLock);
		currentWorkStateBitflag |= thisThreadStateBitflag;
		if (currentWorkStateBitflag == allThreadsFinishedBitflag)
			allThreadsFinished.notify_all();
		allThreadsFinished.wait(lckFin, [&]() { return currentWorkStateBitflag == allThreadsFinishedBitflag; });
	}
}

void MTGenerationCalculator::calculateNextGeneration_impl(unsigned int threadSystemID)
{
	const unsigned int mapHeight = mapPtr->getMapHeight();
	const unsigned int mapWidth = mapPtr->getMapWidth();
	Cell** frontBufferCellArray = mapPtr->getFrontBuffer();
	Cell** backBufferCellArray = mapPtr->getBackBuffer();

	const unsigned int rowsToProcessPerThreadCnt = (mapHeight - 2u) / (threadCnt + 1u);
	const unsigned int firstRowToProcessByThisThread = threadSystemID * rowsToProcessPerThreadCnt + 1u;
	const unsigned int lastRowToProcessByThisThread = threadSystemID == threadCnt ? firstRowToProcessByThisThread + mapHeight - (threadSystemID * rowsToProcessPerThreadCnt) - 3u : firstRowToProcessByThisThread + rowsToProcessPerThreadCnt;

	/*if (threadSystemID == 3u)
		__debugbreak();*/

	for (unsigned int i = firstRowToProcessByThisThread; i <= lastRowToProcessByThisThread; i++)
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