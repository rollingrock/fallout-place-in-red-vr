

namespace PlaceInRed
{
	REL::Relocation<std::uintptr_t> pA{ REL::Offset(0x02020ab) };
	REL::Relocation<std::uintptr_t> pB{ REL::Offset(0x0200fe8) };
	REL::Relocation<std::uintptr_t> pC{ REL::Offset(0x0201fb2) };
	REL::Relocation<std::uintptr_t> pD{ REL::Offset(0x0202448) };
	REL::Relocation<std::uintptr_t> pE{ REL::Offset(0x020b94c) };
	REL::Relocation<std::uintptr_t> pF{ REL::Offset(0x02022fa) };
	REL::Relocation<std::uintptr_t> pG{ REL::Offset(0x0200f1e) };
	REL::Relocation<std::uintptr_t> pH{ REL::Offset(0x0206e2b) };
	REL::Relocation<std::uintptr_t> pJ{ REL::Offset(0x0218d8c) };
	REL::Relocation<std::uintptr_t> pRed{ REL::Offset(0x282d6b7) };
	REL::Relocation<std::uintptr_t> pRedCall{ REL::Offset(0x0202270) };
	REL::Relocation<std::uintptr_t> pYellow{ REL::Offset(0x0204323) };
	REL::Relocation<std::uintptr_t> pWSTimer{ REL::Offset(0x0226dda) };
	REL::Relocation<std::uintptr_t> pGroundSnap{ REL::Offset(0x026316d) };
	REL::Relocation<std::uintptr_t> pObjectSnap{ REL::Offset(0x01ffd86) };
	REL::Relocation<std::uintptr_t> pPowerColorCall{ REL::Offset(0x0216f00) };

	std::uint8_t NOP3[3] = { 0x0F, 0x1F, 0x00 };                                // 3 byte nop
	std::uint8_t NOP4[4] = { 0x0F, 0x1F, 0x40, 0x00 };                          // 4 byte nop
	std::uint8_t NOP5[5] = { 0x0F, 0x1F, 0x44, 0x00, 0x00 };                    // 5 byte nop
	std::uint8_t NOP6[6] = { 0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00 };              // 6 byte nop
	std::uint8_t NOP7[7] = { 0x0F, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x00 };        // 7 byte nop
	std::uint8_t NOP8[8] = { 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00 };  // 8 byte nop
	std::uint8_t pC_old[7];
	std::uint8_t pC_new[7] = { 0x31, 0xC0, 0x0F, 0x1F, 0x44, 0x00, 0x00 };  
	std::uint8_t pD_old[7];
	std::uint8_t pD_new[7] = { 0x31, 0xC0, 0xB0, 0x01, 0x90, 0x90, 0x90 };  //xor al,al;mov al,01;nop x3
	std::uint8_t pF_old[6];
	std::uint8_t pJ_old[2] = { 0x74, 0x35 };
	std::uint8_t pJ_new[2] = { 0xEB, 0x29 };
	std::uint8_t pK_old[6] = { 0x0F, 0x85, 0xCB, 0x00, 0x00, 0x00 };
	std::uint8_t pK_new[7] = { 0xEB, 0x1A, 0x90, 0x90, 0x90, 0x90 };
	std::uint8_t pRedCall_old[5];
	std::uint8_t pYellow_old[3] = { 0x8B, 0x58, 0x14 };
	std::uint8_t pTIMER_old[6] = { 0x0F, 0x84, 0xE5, 0x00, 0x00, 0x00 };
	std::uint8_t pTIMER_new[6] = { 0xE9, 0xDE, 0x00, 0x00, 0x00, 0x90 };  //jmp instead
	std::uint8_t pObjectSnap_old[8];
	std::uint8_t pObjectSnap_new[8] = { 0x0F, 0x57, 0xF6, 0x0F, 0x1F, 0x44, 0x00, 0x00 };  // xorps xmm6, xmm6; NOP5;

	// Simple function to read memory (credit reg2k).
	static bool ReadMemory(uintptr_t addr, void* data, size_t len)
	{
		unsigned long oldProtect;
		if (VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect)) {
			memcpy(data, (void*)addr, len);
			if (VirtualProtect((void*)addr, len, oldProtect, &oldProtect)) {
				return true;
			}
		}
		return false;
	}

	void EnableRedPlacement()
	{
		logger::info("Enabling red placement");

		std::uint8_t data = 0;
		REL::safe_write(pA.address() + 0x6, &data, sizeof(data));

		data = 1;
		REL::safe_write(pA.address() + 0xC, &data, sizeof(data));

		data = 0;
		REL::safe_write(pB.address() + 0x1, &data, sizeof(data));

		REL::safe_write(pC.address(), pC_new, sizeof(pC_new));
		REL::safe_write(pC.address() + 0x10, pK_new, sizeof(pK_new));
		REL::safe_write(pC.address() + 0x21, &data, sizeof(data));

		REL::safe_write(pD.address(), pD_new, sizeof(pD_new));

		data = 0xEB;
		REL::safe_write(pE.address(), &data, sizeof(data));

		REL::safe_write(pF.address(), NOP6, sizeof(NOP6));
		
		data = 0x98;
		REL::safe_write(pG.address() + 0x1, &data, sizeof(data));
		
		data = 0xEB;
		REL::safe_write(pH.address(), &data, sizeof(data));

		REL::safe_write(pJ.address(), pJ_new, sizeof(pJ_new));

		data = 0x0;
		REL::safe_write(pRed.address() + 0xC, &data, sizeof(data));
		REL::safe_write(pRedCall.address(), NOP5, sizeof(NOP5));

		REL::safe_write(pYellow.address(), NOP3, sizeof(NOP3));

		REL::safe_write(pWSTimer.address(), pTIMER_new, sizeof(pTIMER_new));

		data = 0x85;
		REL::safe_write(pGroundSnap.address() + 0x1, &data, sizeof(data));

		REL::safe_write(pObjectSnap.address(), pObjectSnap_new, sizeof(pObjectSnap_new));

		REL::safe_write(pPowerColorCall.address(), NOP5, sizeof(NOP5));
	}

	void Install() {
		logger::info("Installing PlaceInRed");

		ReadMemory(pC.address(), pC_old, sizeof(pC_old));
		ReadMemory(pD.address(), pD_old, sizeof(pD_old));
		ReadMemory(pF.address(), pF_old, sizeof(pF_old));
		ReadMemory(pRedCall.address(), pRedCall_old, sizeof(pRedCall_old));
		ReadMemory(pObjectSnap.address(), pObjectSnap_old, sizeof(pObjectSnap_old));

		EnableRedPlacement();
	}
}
