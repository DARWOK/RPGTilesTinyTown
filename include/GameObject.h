#pragma once
#include "raylib.h"
#include "string"
#include <iostream>
#include <vector>

namespace LoW
{
	class GameObject
	{
	public:
		Vector2 position;
		std::string name;
		/// imgaen del objeto
		Texture texture;
		bool displayName = false;

		// static vector that contains all scene gameobjects
		static std::vector<GameObject*> gameObjects;

		//constructor predeterminado
		GameObject():
			position({0,0}),
			name("GameObject"),
			texture({0}){ }

		// constructor
		GameObject(Vector2 pos, std::string _name, Texture tex) :
			position(pos), name(_name), texture(tex) {}

		// update position
		virtual void update();
		// render object
		virtual void draw();
	};
}

