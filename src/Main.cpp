#include <chrono>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include "Utils/Detection.h"

DWORD GetProcessId(const char* ProcessName)
{
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	if (!Process32First(hSnap, &pe32))
		return NULL;

	do {

		if (!strcmp(pe32.szExeFile, ProcessName))
		{
			CloseHandle(hSnap);
			return pe32.th32ProcessID;
		}

	} while (Process32Next(hSnap, &pe32));

	CloseHandle(hSnap);
	return NULL;
}

std::vector<std::string> GetDLLS(DWORD ProcessID)
{
	HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessID);
	std::vector<std::string> loadedDLLs;

	if(processHandle != NULL)
	{
		HMODULE moduleHandles[1024];
		DWORD cbNeeded;

		if (EnumProcessModules(processHandle, moduleHandles, sizeof(moduleHandles), &cbNeeded))
		{
			DWORD numModules = cbNeeded / sizeof(HMODULE);

			std::vector<char> modulePath(MAX_PATH);

			for(DWORD i = 0; i < numModules; i++)
			{
				if (GetModuleFileNameExA(processHandle, moduleHandles[i], &modulePath[0], MAX_PATH))
				{
					std::string dllPath(modulePath.data());
					loadedDLLs.push_back(dllPath);
				}
			}
		}

		return loadedDLLs;
		CloseHandle(processHandle);
	}
}

int ScanForStrings(const std::string& dllPath)
{
	HANDLE fileHandle = CreateFileA(dllPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD fileSize = GetFileSize(fileHandle, NULL);
		if(fileSize != INVALID_FILE_SIZE)
		{
			std::vector<char> fileContent(fileSize + 1);
			DWORD bytesRead;

			if(ReadFile(fileHandle, fileContent.data(), fileSize, &bytesRead, NULL))
			{
				fileContent[fileSize] = '\0';

				std::string content(fileContent.data());

				std::string searchString = "ReadProcessMemory";
				size_t foundIndex = content.find(searchString);

				if (foundIndex != std::string::npos)
				{
					return 1;
				}
			}
		}
		CloseHandle(fileHandle);
	}
	return 0;
}

void OnDLLChange(std::vector<std::string> dllPaths)
{
	int readout = 0;

	for(int i = 0; i < dllPaths.size(); i++)
	{
		readout = ScanForStrings(dllPaths[i]);

		if(readout == 1)
		{
			std::cout << "[LOG] Possible cheat found in file " << dllPaths[i] << ".\n";
		}

		std::cout << "[LOG] DLL was clean " << dllPaths[i] << ".\n";
		readout = 0;
	}
}

std::vector<std::string> GetNewDLLs(std::vector<std::string> originalList, std::vector<std::string> currentList)
{
	std::vector<std::string> newList;

	for(const auto& dll : currentList)
	{
		if(std::find(originalList.begin(), originalList.end(), dll) == originalList.end())
		{
			newList.push_back(dll);
		}
	}

	return newList;
}

int main()
{ 
	Library library;

	library.Debug = true;

	DWORD pid = 100103;

	library.SetProcessID(pid);

	/*
	bool processFound = false;
	DWORD processID = 0;
	bool isRunning;

	std::vector<std::string> originalDlls;
	std::vector<std::string> currentDlls;
	std::vector<std::string> foundDlls;

	float scanResetTime = 2.0f;

	std::cout << "[LOG] Initiating BAC...\n";

	do
	{
		processID = GetProcessId("Muck.exe");

		if (processID != 0)
		{
			processFound = true;
			std::cout << "[LOG] Process ID found! [" << processID << "]\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(3500));
			originalDlls = GetDLLS(processID);
			std::cout << "[LOG] DLLs Logged.\n";
		}
	} while (processFound != true);

	while(true)
	{
		auto startTime = std::chrono::steady_clock::now();

		currentDlls = GetDLLS(processID);
		if(currentDlls.size() > originalDlls.size())
		{
			std::cout << "[LOG] Change in DLL size: " << (currentDlls.size() - originalDlls.size()) << " PROCESS ID: " << processID << "\n";
			foundDlls = GetNewDLLs(originalDlls, currentDlls);
			OnDLLChange(foundDlls);
			//
			for(int i = 0; i < foundDlls.size(); i++)
			{
				std::cout << "\t[DLLS] " << foundDlls[i] << "\n";
			}
			//
		}

		auto endTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::chrono::milliseconds waitTime(2000);
		std::chrono::milliseconds remainingTime = waitTime - elapsedTime;

		if (remainingTime.count() > 0)
			std::this_thread::sleep_for(remainingTime);
	}
	
	DWORD processID = GetProcessId("Muck.exe");

	std::cout << "NOTEPAD PROCESS ID<< " << processID << "\n";

	std::vector<std::string> dlls = GetDLLS(processID);

	for(int i = 0; i < dlls.size(); i++)
	{
		std::cout << dlls[i] << "\n";
	}

	return 0;
	*/
}