#pragma once
// Se tiene que usar un wrapper porque Raylib truena si incluimos windows.h en el main
// o que alguna biblioteca incluida (como es el caso de MyLibrary.h) inclua windows
// entonces, MyLibrary.h se incluye en MyDLLWrapper.cpp y no aqui

typedef size_t(*WriteCallback)(const char* message);

class MyDLLWrapper
{
public:
	// All functions are static
	static int MBError(const wchar_t* mesage, const wchar_t* boxTitle);
	static int MBWarning(const wchar_t* mesage, const wchar_t* boxTitle);

	// Curl functions
	static int httpGet(const char* url, WriteCallback callback);
};

