#pragma once
#include <thread>
#include <condition_variable>
#include <mutex>
#include <functional>
#include <vector>

#include "IGenerationCalculator.h"

/*
	- destructor truns off all running threads 
	- what if T is void??? (do we need to use static_assert(false) for void?
	- is it possible to do something like this: class Foo : public MTGenerationCalculator<Foo> ?
*/

class MTGenerationCalculator : public IGenerationCalculator
{
public:
	explicit MTGenerationCalculator(unsigned int numberOfThreads);
	virtual ~MTGenerationCalculator();
	
	void execute();
	void closeAllThreads();

	virtual void calculateNextGeneration(Map& map) override;

protected:
	void concurrentFunction(unsigned int threadSystemID); // protected?

private:
	constexpr static unsigned int MAX_THREADS = 16;
	unsigned int threadCnt;

	std::condition_variable allThreadsAreWaiting;
	std::mutex allThreadsAreWaitingLock;
	std::condition_variable dataReadyToProcess;
	std::mutex dataReadyToProcessLock;
	std::condition_variable allThreadsFinished;
	std::mutex  allThreadsFinishedLock;

	std::uint16_t currentStateBitflag;     // 0 - calculating, 1 - waiting
	std::uint16_t currentWorkStateBitflag; // 0 - calculating, 1 - finished
	std::uint16_t allThreadsWaitingBitflag;
	std::uint16_t allThreadsFinishedBitflag;
	static constexpr std::uint16_t allThreadsCalculatingBitflag = 0u;

	bool dataReadyToProcessFlag;
	bool shouldCloseFlag;

	std::vector<std::thread> threads;

	Map* mapPtr;

private:
	inline void waitInMainThreadForAllThreadsToBeReady()
	{
		std::unique_lock lck(allThreadsAreWaitingLock);
		allThreadsAreWaiting.wait(lck, [&]() { return currentStateBitflag == allThreadsWaitingBitflag; }); // deadlock?
	}

	// actual calculation
	void calculateNextGeneration_impl(unsigned int threadSystemID);
};
