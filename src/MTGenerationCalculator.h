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
	MTGenerationCalculator(unsigned int numberOfThreads);
	virtual ~MTGenerationCalculator();
	
	void execute();
	void closeAllThreads();

	virtual void calculateNextGeneration(Map& map) override;

protected:
	void concurrentFunction(unsigned int threadSystemID, Cell** frontBuffer, Cell** backBuffer);

private:
	const static unsigned int MAX_THREADS = 16;
	unsigned int threadCount;

	std::condition_variable startSignal;
	std::unique_lock<std::mutex> mainLock;
	std::condition_variable mainCondVar;

	bool shouldCloseFlag;

	std::vector<std::thread> threads;
	std::vector<std::unique_lock<std::mutex>> locks;

private:
	void runAllThreads();
	void sendStartSignal();
	void waitForStartSignal();
	inline bool shouldClose() const { return shouldCloseFlag; }
	void run(unsigned int threadSystemID);
};
