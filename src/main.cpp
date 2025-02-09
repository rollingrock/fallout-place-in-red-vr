#include "PlaceInRed/PlaceInRed.h"
#include "Scripts/Papyrus.h"



extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);
	F4SE::GetPapyrusInterface()->Register(Papyrus::RegisterFunctions);

	PlaceInRed::EnableInitialDefault();

	return true;
}

