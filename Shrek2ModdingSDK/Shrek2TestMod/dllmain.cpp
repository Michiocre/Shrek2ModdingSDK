#include <windows.h>
#include "Shrek2ModdingSDK.h"
#include <string>

Shrek2 Game = Shrek2();

void OnMapLoad(Shrek2Maps oldMap, Shrek2Maps newMap, std::string rawMap) {
	Game.LogToConsole("Old map: " + Game.Functions.MapIdToString(static_cast<int>(oldMap)) +
		" | New Map: " + Game.Functions.MapIdToString(static_cast<int>(newMap)));

	if (newMap == Shrek2Maps::Shreks_Swamp) {
		Game.LogToConsole("We're in SWAAAMP!");
	}
	else if (newMap == Shrek2Maps::The_Hunt_Part1) {
		Game.LogToConsole("It's hunting time!");
	}
}

void OnCharacterChanged(std::string oldCharacter, std::string newCharacter)
{
	Game.LogToConsole("Old character: " + oldCharacter + " | New character: " + newCharacter);
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnMapLoad = OnMapLoad;
	Game.Events.OnCharacterChanged = OnCharacterChanged;

	Game.Initialize("Shrek 2 Test Mod");
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Game.SetDllHandle(hModule);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitializationThread, NULL, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		if (Game.IsModRunning) {
			Game.IsModRunning = false;
			Sleep(1000);
		}
		break;
	}
	return TRUE;
}