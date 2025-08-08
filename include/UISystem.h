#pragma once
#include <iostream>
#include "View.h"
#include <vector>
#include "Label.h"
#include "raylib.h"
#include "Image.h"
#include "Button.h"


//Singleton for UI management
class UISystem
{
public:
	//////////////////////////////////////////////
	// Patrón singleton: Asegurar que sólo exita una instancia de UISystem
	//////////////////////////////////////////////

	static UISystem& getInstance()
	{
		if (!instance)
		{
			instance = new UISystem();
		}
		return *instance;
	}

	//método para probar el singleton
	void test()
	{
		std::cout << "Hola soy El singleton de UI" << std::endl;
	}
	// también podemos exponer como estático un método para acceder más fácilmente
	static void Test() // es un wrapper o envoltura
	{
		getInstance().test();
	}

	//////////////////////////////////////////////
	// Propiedades espefíficas del sistema de UI
	//////////////////////////////////////////////
	//lista de objetos de UI dibujables
	std::vector<View*> views;

	Label* createLabel(const char* text, int x, int y, int fontSize = 20);

	ImageView* createImage(const char* image, int x, int y, int width = 0, int height = 0);

	Button* createButton(const char* text, int x, int y, int w, int h, int fontsize = 30);
	
	void draw();

	static void Draw()
	{
		getInstance().draw();
	}

	void update();
	static void Update()
	{
		getInstance().update();
	}

private:
	static UISystem* instance;

	UISystem() = default; // Constructor privado para evitar instanciación externa
	UISystem(const UISystem&) = delete; // Eliminar el constructor de copia
	UISystem& operator = (const UISystem&) = delete; // Eliminar el operador de asignación
};

