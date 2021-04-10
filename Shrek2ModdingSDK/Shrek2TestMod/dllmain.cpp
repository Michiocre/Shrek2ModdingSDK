/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#include <windows.h>
#include <string>
#include "Shrek2ModdingSDK.h"
#include "Shrek2DirectX.h"

Shrek2 Game = Shrek2();

void OnTick()
{
	if (Game.Input.OnKeyPress(Shrek2Input::G)) {
		system("CLS");

		Game.LogToConsole("Coins: " + std::to_string(Game.Inventory.GetCoins()));
		Game.LogToConsole("Shamrocks: " + std::to_string(Game.Inventory.GetShamrocks()));
		Game.LogToConsole("Strength Pots: " + std::to_string(Game.Inventory.GetStrengthPotions()));
	}

	if (Game.Input.OnKeyPress(Shrek2Input::H)) {
		Game.Inventory.SetCoins(999);
		Game.Inventory.SetShamrocks(6);
		Game.Inventory.SetStrengthPotions(12);
	}
}

void RenderUI()
{

}

void OnStart()
{
	Shrek2UI::GameWindowSize = Game.GameWindowSize;
	Shrek2UI::RenderUI = RenderUI;
	Shrek2UI::Initialize();
}

DWORD WINAPI InitializationThread(HINSTANCE hModule)
{
	Game.Events.OnStart = OnStart;
	Game.Events.OnTick = OnTick;

	Game.Initialize("Shrek 2 Test Mod", true);

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
			Shrek2UI::StopUI();
			Sleep(1000);
		}
		break;
	}
	return TRUE;
}