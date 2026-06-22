// ExampleMod.cpp : Defines the entry point for the application.
//

#include "ExampleMod.h"

#include <Plant.h>

extern "C" __declspec(dllexport) void ModInit(const std::string* theDllName)
{
	std::cout << "Hello from mod " << *theDllName << "! MSVC version : " << _MSC_VER << std::endl;

	std::cout << Plant::GetNameString(SEED_SNOWPEA)	<< " eaten!" << std::endl;
}