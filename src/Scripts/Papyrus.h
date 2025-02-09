#pragma once


namespace Papyrus
{
	bool RegisterFunctions(RE::BSScript::IVirtualMachine* a_vm)
	{
		logger::info("Registering functions");
		return true;
	}
}
