#pragma once

#include "Map.h"

class IGenerationCalculator
{
public:
	virtual void calculateNextGeneration(Map& map) = 0;

	virtual ~IGenerationCalculator() {};

protected:
	IGenerationCalculator() = default;
	IGenerationCalculator(const IGenerationCalculator&) = delete;
	IGenerationCalculator(IGenerationCalculator&&) = delete;
};
