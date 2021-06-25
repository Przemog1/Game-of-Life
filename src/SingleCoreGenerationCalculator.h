#pragma once

#include "IGenerationCalculator.h"


class SingleCoreGenerationCalculator final : public IGenerationCalculator
{
public:
	virtual void calculateNextGeneration(Map& map) override;

	~SingleCoreGenerationCalculator() = default;
};
