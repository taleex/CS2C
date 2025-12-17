#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <stdexcept>

#include "src/core/interfaces.hpp"

DWORD WINAPI cheat_thread(LPVOID instance){

	try {
		interfaces::create();
	} catch (const std::exception& e) {
		interfaces::destroy();
		MessageBoxA(nullptr, e.what(), "Error", MB_ICONERROR);
		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(instance), 1);
		return 0;
	}

	while (!(GetAsyncKeyState(VK_END) & 1)){
		Sleep(100);
	}

	interfaces::destroy();

	MessageBoxA(nullptr, "Cheat unloaded successfully.", "Info", MB_ICONINFORMATION);

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	return 0;
}


DWORD APIENTRY DllMain(HINSTANCE instance, DWORD reason, LPVOID) {

	if (reason == DLL_PROCESS_ATTACH){
		DisableThreadLibraryCalls(instance);

		HANDLE thread = CreateThread(nullptr, 0, cheat_thread,instance,0,nullptr);
		if (thread != INVALID_HANDLE_VALUE){
			CloseHandle(thread);
			return true;
		}
	}

	return false;

}