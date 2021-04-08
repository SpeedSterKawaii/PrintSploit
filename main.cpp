// PrintSploit - Remade by Elkoax's Print Exploit.
//Credits to Elkoax and SpeedSterKawaii B
#include "pch.h"
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include "address.h"
#pragma warning(disable : 4996). // I hate when warnings aappear.
using namespace std;
void ConsoleBypass(const char* Title) {
	DWORD aaaa;
	VirtualProtect((PVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &aaaa);
	*(BYTE*)(&FreeConsole) = 0xC3;
	AllocConsole();
	SetConsoleTitleA(Title);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}
void SendPrintScript(std::string script)
{
	std::string yeet = script;
	printerf(1, yeet.c_str());
}
DWORD WINAPI CreatePipe(PVOID lvpParameter)
{
	string WholeScript = "";
	HANDLE hPipe;
	char buffer[999999];
	DWORD dwRead;
	hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\PrintPipe"), // This is the Pipe so we Can Send Scripts.
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != INVALID_HANDLE_VALUE)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				buffer[dwRead] = '\0';
				try {
					try {
						WholeScript = WholeScript + buffer;
					}
					catch (...) {
					}
				}
				catch (std::exception e) {

				}
				catch (...) {

				}
			}
			SendPrintScript(WholeScript);
			WholeScript = "";
		}
		DisconnectNamedPipe(hPipe);
	}
}
void main()
{
	ConsoleBypass("PrintSploit | SpeedSterKawaii");
	std::cout << "PrintHax by SpeedSterKawaii.\n";
	std::cout << "Originally made by Elkoax.\n";
	std::cout << "Lets check print address/ccv.\n";
	if (!printerf)
	{
		std::cout << "Oh No, Please Update Print address!\n"; // Update the print address.
		getchar();
		exit(0);
	}
	else
	{
		std::cout << "Yes, Print Address/CCV is Updated!\n";
	}
	std::cout << "Creating print pipe.\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CreatePipe, NULL, NULL, NULL);
	std::cout << "Pipe has been done.\n";
	std::cout << "You can now execute prints!\n";
	// Info Print: 1
	// Error Print: 3
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, void* Reserved)
{
	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(Module);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default: break;
	}

	return TRUE;
}

