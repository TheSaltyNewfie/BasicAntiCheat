#include "Detection.h"

using std::vector;
using std::string;

void Library::Initialize(DWORD processID, bool enableDebug) {
    debugMode = enableDebug;
    AssignProcessID(processID);
    InitializeLibraries();
}

vector<string> Library::CompareLibrarySnapshots(const vector<string>& previousSnapshot) {
    

    return vector<string>();
}

vector<string> Library::UpdateLibraries(vector<string> snapshot) {
    vector<string> refresh;

    for (const auto& dll : snapshot) {
        if (std::find(libraries.begin(), libraries.end(), dll) == libraries.end()) {
            refresh.push_back(dll);
        }
    }
    return refresh;
}

vector<string> Library::GetCurrentLibraries() {
    return libraries;
}

void Library::AssignProcessID(DWORD processID) {
    gameProcessID = processID;

    if (debugMode) {
        print("[+] ProcessID is set to %d", gameProcessID);
    }
}

void Library::InitializeLibraries() {
    HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, gameProcessID);

    if (processHandle != NULL) {
        HMODULE moduleHandles[1024];
        DWORD cbNeeded;

        if (EnumProcessModules(processHandle, moduleHandles, sizeof(moduleHandles), &cbNeeded)) {
            DWORD numModules = cbNeeded / sizeof(HMODULE);
            vector<char> modulePath(MAX_PATH);

            for (DWORD i = 0; i < numModules; i++) {
                if (GetModuleFileNameExA(processHandle, moduleHandles[i], &modulePath[0], MAX_PATH)) {
                    string dllPath(modulePath.data());
                    libraries.push_back(dllPath);
                    if (debugMode) {
                        print("[//] %s\n", dllPath.c_str());
                    }
                }
            }
        }
        CloseHandle(processHandle);
    }
}
