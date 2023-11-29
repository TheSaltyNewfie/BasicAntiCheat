#include "Attach.h"

DWORD Attach::GetProcessID(const char* ProcessName)
{
	DWORD pid = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	if (!Process32First(hSnap, &pe32))
		return NULL;

	do
	{
		if (!strcmp(pe32.szExeFile, ProcessName))
		{
			CloseHandle(hSnap);
			return pe32.th32ProcessID;
		}
	} while (Process32Next(hSnap, &pe32));

	CloseHandle(hSnap);
	return 0;
}

/*
void Attach::InjectBACInternal(const char* dllPath)
{
	DWORD ProcessID = Attach::GetProcessID("javaw.exe");

	printf("[Attach][Log]: Process ID: %i\n", ProcessID);

	if (ProcessID == NULL)
		printf("[Attach][Error]: Failed to get process ID\n");
	printf("[Attach][Success]: Got process ID\n");

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
	if(hProcess == NULL)
		printf("[Attach][Error]: Failed to get process handle\n");
	printf("[Attach][Success]: Got process handle\n");

	LPVOID pDLLPath = VirtualAllocEx(hProcess, NULL, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
	if(pDLLPath == NULL)
		printf("[Attach][Error]: Failed to allocate memory for %c\n", dllPath);
	printf("[Attach][Success]: Allocated Memory for %c\n", dllPath);

	if(!WriteProcessMemory(hProcess, pDLLPath, dllPath, strlen(dllPath) + 1, NULL))
		printf("[Attach][Error]: Failed WriteProcessMemory\n");
	printf("[Attach][Success]: Wrote process memory\n");

	LPVOID pLoadLibraryA = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if(pLoadLibraryA == NULL)
		printf("[Attach][Error]: Failed to load DLL\n");
	printf("[Attach][Success]: Loaded DLL\n");

	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pLoadLibraryA, pDLLPath, 0, NULL);
	if (hThread == NULL)
		printf("[Attach][Error]: Failed to create remote thread\n");
	printf("[Attach][Success]: Created remote thread\n");

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFreeEx(hProcess, pDLLPath, 0, MEM_RELEASE);
	CloseHandle(hProcess);
}
*/