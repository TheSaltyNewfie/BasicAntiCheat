#pragma once
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>

class Strings
{
public:
	std::vector<std::string> GetStrings(bool allStrings);
	int Scan(const std::string& dllPath);

private:
	std::vector<std::string> AllStrings;
	std::vector<std::string> DetectedStrings;

	void SetStrings();
};

class Library
{
public:
	bool Debug = false;
	DWORD GameProcessID;

	std::vector<std::string> GetLibraries();

	void SetProcessID(DWORD ProcessID);

private:
	std::vector<std::string> Libraries;

	void SetLibraries();
};