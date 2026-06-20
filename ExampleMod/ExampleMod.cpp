// ExampleMod.cpp : Defines the entry point for the application.
//

#include "ExampleMod.h"
#include "Events.h"

class Team;

enum class FacingDirection : bool
{
	STREET,
	LAWN
};

struct LivingAttributes
{
	Team* mTeam;
	FacingDirection mFacingDirection;
	int mSpeed;
	int mTickRate;
	bool mTargetable : 1;
	bool m : 1;
};

extern "C" __declspec(dllexport) void ModInit(const std::string* theDllName)
{
	std::cout << "Hello from mod " << *theDllName << "! MSVC version : " << _MSC_VER << std::endl;
	Events::PLANT_EATEN += [](PlantEatenContext& theContext)
		{
			
		};
}