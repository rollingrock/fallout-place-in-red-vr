#pragma once

#include "PlaceInRed/PlaceInRed.h"

namespace Papyrus
{
	namespace detail
	{
		void EnablePlaceInRed(std::monostate) {
			PlaceInRed::Patches::PatchRed(true);
		}

		void DisablePlaceInRed(std::monostate) {
			PlaceInRed::Patches::PatchRed(false);
		}

		void EnableGroundSnap(std::monostate) {
			PlaceInRed::Patches::PatchGroundSnap(true);
		}

		void DisableGroundSnap(std::monostate) {
			PlaceInRed::Patches::PatchGroundSnap(false);
		}

		void EnableObjectSnap(std::monostate) {
			PlaceInRed::Patches::PatchObjectSnap(true);
		}

		void DisableObjectSnap(std::monostate) {
			PlaceInRed::Patches::PatchObjectSnap(false);
		}

		void EnableOutlines(std::monostate) {
			PlaceInRed::Patches::PatchOutlines(true);
		}

		void DisableOutlines(std::monostate) {
			PlaceInRed::Patches::PatchOutlines(false);
		}
	}


	bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		logger::info("Registering functions");

		a_vm->BindNativeMethod("PlaceInRedVR", "EnablePlaceInRed", detail::EnablePlaceInRed, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "DisablePlaceInRed", detail::DisablePlaceInRed, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "EnableGroundSnap", detail::EnableGroundSnap, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "DisableGroundSnap", detail::DisableGroundSnap, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "EnableObjectSnap", detail::EnableObjectSnap, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "DisableObjectSnap", detail::DisableObjectSnap, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "EnableOutlines", detail::EnableOutlines, true);
		a_vm->BindNativeMethod("PlaceInRedVR", "DisableOutlines", detail::DisableOutlines, true);

		logger::info("Functions Registered");
		return true;
	}
}
