#pragma once
#include "GameObject.h"
#include "IAttacker.h"
#include "iostream"

namespace LoW
{
	class Player; // Forward declaration
	class Weapon : public GameObject, public IAttacker
	{
	public:

		// Whos carrying the weapon
		Player* owner;
		Vector2 offset; // Weapon offset relative to the player

		// Constructor
		Weapon (Vector2 pos, std::string _name, Texture tex):
			GameObject(pos, _name, tex)
		{
			owner = nullptr; // Inicialmente no tiene dueño
			offset = {30.0f, 10.0f};
		}

		void Fire() override
		{
			// Implementación del ataque
			std::cout << "Weapon Fired" << std::endl;
		}

		void update() override
		{
			//if (owner != nullptr)
			//{
			//	// Actualiar la posición del arma según la del jugador
			//	position = owner->position + offset;
			//}
		}

		void draw() override
		{
			Rectangle r = { 0,0,64,64 };
			DrawTextureRec(texture, r, position, WHITE);
		}
	};
}

