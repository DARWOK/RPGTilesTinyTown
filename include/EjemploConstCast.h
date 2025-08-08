#pragma once
#include <iostream>

class EjemploConstCast
{
	static void ejemploCast()
	{
		const int x = 10;
		int* p = const_cast<int*>(&x); // Eliminar la constancia0
		*p = 20; // no se puede porque lo marcamos como const
		std::cout << "Valor de x: " << x << std::endl; //Imprime 20
	}
};

