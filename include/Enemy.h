#pragma once
#include "GameObject.h"

using namespace LoW;

class Enemy : public GameObject
{
public:

	Enemy(Vector2 pos, std::string _name, Texture tex) :
		GameObject(pos, _name, tex)
	{

	}
};