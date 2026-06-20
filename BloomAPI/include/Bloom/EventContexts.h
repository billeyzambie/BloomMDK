#pragma once

#include "../Lawn/Plant.h"
#include "../Lawn/Zombie.h"
#include "Bloom.h"

struct BLOOM_API PlantEatenContext
{
	bool mCanceled;
	Plant *mEatenPlant;
	Zombie *mEaterZombie;
};