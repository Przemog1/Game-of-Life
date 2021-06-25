#include "MTGenerationCalculator.h"
#include <algorithm>

MTGenerationCalculator::MTGenerationCalculator(unsigned int numberOfThreads)
	:shouldCloseFlag(false)
{
	if (numberOfThreads == 0)
		numberOfThreads = 1;
	if (numberOfThreads > MAX_THREADS)
		numberOfThreads = MAX_THREADS;

	threads.reserve(numberOfThreads);
	locks.reserve(numberOfThreads);

	for (int i = 0; i < numberOfThreads; i++)
		locks.push_back(std::unique_lock<std::mutex>());

	runAllThreads();
}

void MTGenerationCalculator::runAllThreads()
{
	for (int i = 0; i < threadCount; i++)
	{
		std::thread thread = std::thread(&MTGenerationCalculator::run, this, i);
		threads.push_back(std::move(thread));
		threads[i].detach();
	}
}

void MTGenerationCalculator::run(unsigned int threadSystemID)
{
	while (!shouldClose())
	{
		waitForStartSignal();

		locks[threadSystemID].lock();
		concurrentFunction(threadSystemID);
		locks[threadSystemID].unlock();
	}
}

void MTGenerationCalculator::waitForStartSignal()
{
	mainCondVar.wait(mainLock);
}

MTGenerationCalculator::~MTGenerationCalculator()
{
	sendStartSignal();
	closeAllThreads();
}

void MTGenerationCalculator::sendStartSignal()
{
	for (auto& lock : locks)
	{
		lock.lock();
		lock.unlock();
	}
	startSignal.notify_all();
}

void MTGenerationCalculator::calculateNextGeneration(Map& map)
{

}

void MTGenerationCalculator::concurrentFunction(unsigned int threadSystemID, Cell** frontBuffer, Cell** backBuffer)
{

}

void MTGenerationCalculator::execute()
{
	sendStartSignal();
}

void MTGenerationCalculator::closeAllThreads()
{
	shouldCloseFlag = true;
}