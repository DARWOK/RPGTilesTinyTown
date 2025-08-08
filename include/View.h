#pragma once
#include "raylib.h"

// Base class for all UI elements
class View
{
public:
	Rectangle rect;
	bool visible = true;

	// Default constructor
	View() : rect({0,0,100,100}), visible (true){}
	// Constructor with parameters
	View(int x, int y, int w, int h) : visible(true)
	{
		rect = { (float)x, (float)y, (float)w, (float)h };
	}

	virtual void update() = 0; // método virtual puro, debe ser implementado por las clases derivadas
	virtual void draw() = 0;

protected:
};

