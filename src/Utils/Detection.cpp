#include "Detection.h"

int Strings::Scan(const std::string& dllPath)
{
	/*
	This function is public. Scans all strings from within a specific DLL
	*/
	return 1;
}

void Strings::SetStrings()
{
	/*
	This function is private. Only sets the strings AllStrings and DetectedStrings
	*/

}

void Library::SetProcessID(DWORD ProcessID)
{
	/*
	This function is public. Sets the process ID for the Library Class
	*/
	GameProcessID = ProcessID;

	if (Debug)
		printf("[LibraryClass] ProcessID is set to %i\n", GameProcessID);
}

void Library::SetLibraries()
{
	/*
	This function is private. Sets the libraries currently in the program
	*/


}
