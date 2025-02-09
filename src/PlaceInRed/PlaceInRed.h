#pragma once

#include "Settings/Settings.h"

namespace PlaceInRed
{
	class Patches
	{
	public:
		static void PatchRed(bool enable)
		{
			std::array<std::uint8_t, 8> code, nop;
			code.fill(0x90);  // NOP
			nop.fill(0x90);  // NOP

			auto setCode = [&code](std::initializer_list<std::uint8_t> values) {
				std::copy(values.begin(), values.end(), code.begin());
			};

			// single byte patches
			code[0] = enable ? 0x0 : 0x1;
			Patch<0x02020ab + 0x06>::Install(code.data(), 1);  // A1
			Patch<0x0200fe8 + 0x01>::Install(code.data(), 1);  // B
			Patch<0x0201fb2 + 0x21>::Install(code.data(), 1);   // C3
			Patch<0x282d6c8 + 0x06>::Install(code.data(), 1);  // RED
			code[0] = enable ? 0x1 : 0x2;
			Patch<0x02020ab + 0x0C>::Install(code.data(), 1);   // A2
			code[0] = enable ? 0xEB : 0x76;
			Patch<0x020b94c>::Install(code.data(), 1);          // E
			code[0] = enable ? 0x98 : 0x95;
			Patch<0x0200f1e + 0x1>::Install(code.data(), 1);    // G
			code[0] = enable ? 0xEB : 0x74;
			Patch<0x0206e2b>::Install(code.data(), 1);          // H

			// multi-byte patches
			if (enable) {
				setCode({ 0x31, 0xC0, 0x0F, 0x1F, 0x44, 0x00, 0x00, 0x00});
				Patch<0x0201fb2>::Install(code.data(), 7);      // C1
				setCode({ 0xEB, 0x1A, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });
				Patch<0x0201fb2 + 0x10>::Install(code.data(), 6);      // C2
				setCode({ 0x31, 0xC0, 0xB0, 0x01, 0x90, 0x90, 0x90, 0x90 });
				Patch<0x0202448>::Install(code.data(), 7);  // D
				Patch<0x02022fa>::Install(nop.data(), 6);  // F
				setCode({ 0xEB, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
				Patch<0x0218d8c>::Install(code.data(), 2);  // J
				Patch<0x0202270>::Install(nop.data(), 5);  // Red Caller
				Patch<0x0204323>::Install(nop.data(), 3);  // Yellow override
				Patch<0x0216f00>::Install(nop.data(), 5);  // Power Color Override
				setCode({ 0xE9, 0xDE, 0x00, 0x00, 0x00, 0x90, 0x90, 0x90 });
				Patch<0x0226dda>::Install(code.data(), 6);  // WSTimer

				logger::info("Patches for placing in red enabled");
			} 
			else {
				setCode({ 0x0F, 0xB6, 0x05, 0x2E, 0xF5, 0x73, 0x05, 0x90});
				Patch<0x0201fb2>::Install(code.data(), 7);      // C1
				setCode({ 0x0F, 0x85, 0xCB, 0x00, 0x00, 0x00, 0x90, 0x90 });
				Patch<0x0201fb2 + 0x10>::Install(code.data(), 6);      // C2
				setCode({ 0x0F, 0xB6, 0x05, 0xA2, 0xF0, 0x73, 0x05, 0x90 });
				Patch<0x0202448>::Install(code.data(), 7);  // D
				setCode({ 0x88, 0x05, 0xE8, 0xF1, 0x73, 0x05, 0x90, 0x90 });
				Patch<0x02022fa>::Install(code.data(), 6);  // F
				setCode({ 0x74, 0x2E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 });
				Patch<0x0218d8c>::Install(code.data(), 2);  // J
				setCode({ 0xE8, 0x1B, 0x9C, 0x00, 0x00, 0x00, 0x00, 0x00 });
				Patch<0x0202270>::Install(code.data(), 5);  // Red Caller
				setCode({ 0x8b, 0x58, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00 });
				Patch<0x0204323>::Install(code.data(), 3);  // Yellow override
				setCode({ 0xE8, 0x5B, 0x67, 0x61, 0x02, 0x00, 0x00, 0x00 });
				Patch<0x0216f00>::Install(code.data(), 5);  // Power Color Override
				setCode({ 0x0F, 0x84, 0xE5, 0x00, 0x00, 0x00, 0x90, 0x90 });
				Patch<0x0226dda>::Install(code.data(), 6);  // WSTimer
				logger::info("Patches for placing in red disabled");
			}

		}

		static void PatchGroundSnap(bool enable)
		{
			std::uint8_t code = enable ? 0x86 : 0x85;
			Patch<0x026316d + 0x1>::Install(&code, 1); 

			if (enable) {
				logger::info("Ground snap enabled");
			} else {
				logger::info("Ground snap disabled");
			}
		}

		static void PatchObjectSnap(bool enable)
		{
			if (enable) {
				std::array<std::uint8_t, 8> code = { 0xF3, 0x0F, 0x10, 0x35, 0x5A, 0x33, 0x50, 0x03};
				Patch<0x01ffd86>::Install(code.data(), 8);  
			} else {
				std::array<std::uint8_t, 8> code = { 0x0F, 0x57, 0xF6, 0x0F, 0x1F, 0x44, 0x00, 0x00 };
				Patch<0x01ffd86>::Install(code.data(), 8); 
			}
			if (enable) {
				logger::info("Object snap enabled");
			} else {
				logger::info("Object snap disabled");
			}
		}

		static void PatchOutlines(bool enable)
		{
			std::uint8_t code = enable ? 0x01 : 0x00;
			Patch<0x01f5c80 + 0x6>::Install(&code, 1); 

			code = enable ? 0x76 : 0xEB;
			Patch<0x01f5c80 + 0xD>::Install(&code, 1); 

			if (enable) {
				logger::info("Outlines enabled");
			} else {
				logger::info("Outlines disabled");
			}
		}

	private:
		template <std::uint64_t offset>
		class Patch
		{
		public:
			static void Install(std::uint8_t* a_data, size_t a_size) {
				REL::Relocation<std::uintptr_t> target{ REL::Offset(offset)};
				REL::safe_write(target.address(), a_data, a_size);
			}
		};
	};

	void EnableInitialDefault() {
		logger::info("Enabling Initial Defaults");
		Patches::PatchRed(*Settings::EnableRedPlacement);
		Patches::PatchGroundSnap(*Settings::EnableGroundSnap);
		Patches::PatchObjectSnap(*Settings::EnableObjectSnap);
		Patches::PatchOutlines(*Settings::EnableOutlines);
		logger::info("Initial Defaults Installed");
	}
}
