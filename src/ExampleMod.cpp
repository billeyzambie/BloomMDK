// ExampleMod.cpp : Defines the entry point for the application.
//

#include "ExampleMod.h"

#include <Plant.h>
#include <Events.h>

#include <LawnApp.h>
#include <Board.h>
#include <TodFoley.h>

extern "C" __declspec(dllexport) void ModInit(const std::string* theDllName)
{
	std::cout << "Hello from mod " << *theDllName << "! MSVC version : " << _MSC_VER << std::endl;

	std::cout << Plant::GetNameString(SEED_SNOWPEA)	<< " says hi" << std::endl;

	Events::Subscribe(+[](PlantEatenContext& theContext)
		{
			auto* aPlant = theContext.mEatenPlant;

			int aPosX = aPlant->mX + aPlant->mWidth / 2;
			int aPosY = aPlant->mY + aPlant->mHeight / 2;
			int aDamageRangeFlags = aPlant->GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

			aPlant->mApp->PlayFoley(FoleyType::FOLEY_CHERRYBOMB);
			aPlant->mApp->PlayFoley(FoleyType::FOLEY_JUICY);

			aPlant->mBoard->KillAllZombiesInRadius(aPlant->mRow, aPosX, aPosY, 115, 1, true, aDamageRangeFlags);

			aPlant->mApp->AddTodParticle(aPosX, aPosY, (int)RenderLayer::RENDER_LAYER_TOP, ParticleEffect::PARTICLE_POWIE);
			aPlant->mBoard->ShakeBoard(3, -4);

			aPlant->Die();

			std::cout << Plant::GetNameString(theContext.mEatenPlant->mSeedType) << " eaten" << std::endl;
		});
}