#pragma once
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>

class Attach
{
public:
	const char* ProcessName;

	DWORD GetProcessID(const char* ProcessName);

	//void InjectBACInternal(const char* dllPath);
private:
};