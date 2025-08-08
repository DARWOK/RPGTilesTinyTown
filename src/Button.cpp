#include "Button.h"
#include <iostream>

void Button::update()
{
	if (CheckCollisionPointRec(GetMousePosition(), rect))
	{
		std::cout << "collision" << std::endl;
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			Enemy* troll = new Enemy({ (float)GetRandomValue(1,800),(float)GetRandomValue(1,800) }, "troll", LoadTexture("troll.png"));
			GameObject::gameObjects.push_back(troll);
			std::cout << "Spawn Enemy" << std::endl;
		}
	}
}

void Button::draw()
{
	DrawRectangle(rect.x, rect.y, rect.width, rect.height, RAYWHITE);
	DrawText(text, rect.x, rect.y, fontSize, BLACK);
}