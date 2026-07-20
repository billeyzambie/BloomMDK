#include <iostream>

#include <StoreItem/StoreItemTypes.h>
#include <StoreItem/StoreItemGroups.h>
#include <Registries.h>

#include <TodFoley.h>
#include <LawnApp.h>
#include <Board.h>
#include <PlantEatenContext.h>
#include <Events.h>

const RegistryTypeHolder<StoreItemType>& BRAIN = Registries::STORE_ITEMS.Register([]() {
	StoreItemAttributes anAttributes;
	anAttributes.mCost = 200;
	anAttributes.mDrawOffsetX = 9;
	anAttributes.mDrawOffsetY = 37;
	anAttributes.mIcon = Sexy::IMAGE_BRAIN_ID;
	anAttributes.mBuyCount = 2;
	anAttributes.mMaxBuyCount = 10;
	StoreItemType* aStoreItemType = new StoreItemType("examplemod", "brain", anAttributes);

	aStoreItemType->mGroup = StoreItemGroups::UPGRADES;

	return aStoreItemType;
});

extern "C" __declspec(dllexport) void ModInit(const std::string* theDllName)
{
	std::cout << "Hello from mod " << *theDllName << "! MSVC version : " << _MSC_VER << std::endl;
	ReplaceStoreItemSpot(3, 6, BRAIN);

	Events::Subscribe(+[](PlantEatenContext& theContext)
		{
			auto* aPlant = theContext.mEatenPlant;

			PlayerInfo* aPlayerInfo = aPlant->mApp->mPlayerInfo;

			StoreItem& aBrainStoreItemData = aPlayerInfo->GetStoreItemData(BRAIN);

			if (aBrainStoreItemData.mPurchases <= 0)
				return;

			aBrainStoreItemData.mPurchases--;

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