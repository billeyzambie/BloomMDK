#pragma once

#include "Event.h"
#include "EventContexts.h"
#include "Bloom.h"

namespace Events
{

BLOOM_GLOBAL Event<PlantEatenContext> PLANT_EATEN;

}