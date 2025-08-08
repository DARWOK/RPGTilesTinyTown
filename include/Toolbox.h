#pragma once
#include <iostream>
#include <string>

// Funciones misc

class Toolbox
{
public:
	int id;
	std::string name;

	void Log(const char* msj)
	{
		std::cout << "[Toolbox] " << msj << std::endl;
	}

};

