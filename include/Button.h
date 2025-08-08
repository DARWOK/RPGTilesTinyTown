#pragma once
#include "View.h"
#include "Enemy.h"

class Button :
	public View
{
public:
	const char* text = "Click -> Spawn";
	int fontSize = 30;

	void update() override;
	void draw() override;
};