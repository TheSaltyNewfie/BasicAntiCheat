#include <cstdio>

template <typename... Args>
void print(const std::string& fmt, Args... args)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int color = 7;

	if (fmt.find("[!]") != std::string::npos) 
		color = 4;

	if (fmt.find("[+]") != std::string::npos)
		color = 2;

	if (fmt.find("[//]") != std::string::npos)
		color = 3;

	SetConsoleTextAttribute(hConsole, color);

	char buffer[1024];
    snprintf(buffer, sizeof(buffer), fmt.c_str(), args...);

    std::cout << buffer << std::endl;

	SetConsoleTextAttribute(hConsole, 7);
}