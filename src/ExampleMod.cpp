// ExampleMod.cpp : Defines the entry point for the application.
//

#include "ExampleMod.h"

#include <Plant.h>
#include <Events.h>
#include <EventContexts.h>

extern "C" __declspec(dllexport) void ModInit(const std::string* theDllName)
{
	std::cout << "Hello from mod " << *theDllName << "! MSVC version : " << _MSC_VER << std::endl;

	std::cout << Plant::GetNameString(SEED_SNOWPEA)	<< " says hi" << std::endl;

	Events::Subscribe(+[](PlantEatenContext& theContext)
		{
			std::cout << Plant::GetNameString(theContext.mEatenPlant->mSeedType) << " eaten" << std::endl;
		});
}