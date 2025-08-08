#pragma once

template <typename T>

class Singleton
{
public:
	static T& instance()
	{
		// Accesor principal de nuestro singleton
		static T instance; // Instancia única
		return instance;
	}

	// Por convención, se deben desactivar los constructores de copia y asignación
	Singleton(const Singleton&) = delete;            // No se puede copiar
	// = es el operador de asignación
	Singleton& operator=(const Singleton&) = delete; // No se puede asignar

	// Por convención, un singleton protege el contstructor y destructor
	// No se desactivan porque puede ser llamado desde la clase derivada

protected:
	Singleton() {}  // Constructor protegido
	~Singleton() {} // Destructor protegido
};