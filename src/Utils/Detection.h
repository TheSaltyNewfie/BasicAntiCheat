#pragma once
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <vector>
#include "logging.h"

class Strings
{
public:
	// Implement strings at a later date

private:
	
};

class Library {
public:
    void Initialize(DWORD processID, bool enableDebug);
    std::vector<std::string> CompareLibrarySnapshots(const std::vector<std::string>& previousSnapshot);
    std::vector<std::string> UpdateLibraries(std::vector<std::string> snapshot);
    std::vector<std::string> GetCurrentLibraries();
    void AssignProcessID(DWORD processID);

private:
    DWORD gameProcessID;
    bool debugMode = false;
    std::vector<std::string> libraries;

    void InitializeLibraries();
};