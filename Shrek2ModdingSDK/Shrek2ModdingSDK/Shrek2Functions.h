#pragma once
class Shrek2Functions
{
public:
	typedef void(__cdecl* Shrek2DeleteSaveGame)(int num);
	Shrek2DeleteSaveGame _DeleteSaveGame;

	Shrek2Functions() {
	}
	Shrek2Functions(std::string dllName) {
		_DeleteSaveGame = (Shrek2DeleteSaveGame)GetProcAddress(GetModuleHandle(TEXT("Core.dll")), "?KWDeleteSaveGame@@YAXH@Z");
		DllName = dllName;
	}
	void ExecuteConsoleCommand(std::string command);
	void ExecuteConsoleCommands(std::list<std::string> commands);
	void CC(std::string command);
	void CCS(std::list<std::string> commands);
	void OpenMap(Shrek2Maps map);
	void OpenMap(std::string map);
	void Ghost();
	void Walk();
	void Fly();
	void ToggleFreeCam();
	void DeleteSaveGame(int slot);
	std::string MapIdToString(int mapId);
private:
	void ExecCC(std::string command);
	void ExecCCS(std::list<std::string> commands);
	void Exec();
	std::string DllName;
};

