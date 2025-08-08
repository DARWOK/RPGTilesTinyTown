#include "Player.h"
#include <string>
#include "IAttacker.h"
#include "iostream"

using namespace LoW;

// sobrecargar la función update de GameObject para mover el objeto con las teclas
void Player::update()
{
	if (IsKeyDown(KEY_A))
	{
		position.x -= speed*GetFrameTime();
		animData.direction = ANIM_LEFT;
	}
	if (IsKeyDown(KEY_D))
	{
		position.x += speed*GetFrameTime();
		animData.direction = ANIM_RIGHT;
	}
	if (IsKeyDown(KEY_W))
	{
		position.y -= speed*GetFrameTime();
		animData.direction = ANIM_UP;
	}
	if (IsKeyDown(KEY_S))
	{
		position.y += speed*GetFrameTime();
		animData.direction = ANIM_DOWN;
	}

	// Calcular el frame de la animación
	animData.frameCounter++;
	if (animData.frameCounter > animData.frameSpeed)
	{
		animData.frameCounter = 0;
		animData.currentFrame++;

		if (animData.currentFrame >= animData.maxFrames)
			animData.currentFrame = 0;

		//std::cout << "Frame: " << animData.currentFrame << std::endl;
	}

	// Si tiene arma, hacer que se mueva con eljugador
	if (weapon)
	{
		Weapon* w = dynamic_cast<Weapon*>(weapon);
		w->position = Vector2Add(position, w->offset);
	}

	// Detectar colisiones con armas tiradas en el suelo,
	// iterando en el vector de gameObjects y casteando a Weapon
	for (GameObject* obj : GameObject::gameObjects)
	{
		Weapon* w = dynamic_cast<Weapon*>(obj);
		if (w &&
			w->owner == nullptr && //no tiene dueño
			CheckCollisionRecs({ position.x, position.y, animData.spriteWidth, animData.spriteHeight },
				{ w->position.x,w->position.y, 64,64 })) //asumiendo que las armas son de 64x64
		{
			//std::cout << "Colision con arma: " << w->name << std::endl;
			//SetWeapon(w); // change player's weapon
			shouldPromptForWeapon = true;

			if (IsKeyPressed(KEY_F)) // If F is pressed
			{
				SetWeapon(w); // Change player's weapon
				shouldPromptForWeapon = false;
			}
			break; // exit bucle if a weapon is found
		}
		else shouldPromptForWeapon = false; // There is no weapon nearby
	}

}

void Player::draw()
{
	Rectangle r = { animData.spriteWidth * animData.currentFrame,
					animData.spriteHeight * animData.direction,
					animData.spriteWidth,
					animData.spriteHeight };
	DrawTextureRec(texture, r, position, WHITE);

	if (shouldPromptForWeapon) DrawText(weaponPrompt, 20, GetScreenHeight() - 40, 20, YELLOW);
}

IAttacker* Player::SetWeapon(IAttacker* newWeapon)
{
	if (newWeapon)
	{
		weapon = newWeapon;
		Weapon* w = dynamic_cast<Weapon*>(weapon);
		if (w)
		{
			w->owner = this; // Asignar el owner al arma
			std::cout << "Cambiando arma a " << w->name << std::endl;
		}

		//notificar a los sidekicks
		for (int i = 0; i < 3; i++)
		{
			if (sidekicks[i])
			{
				//sidekicks[i]->SetWeapon(newWeapon);
			}
		}
		return weapon;
	}
	return nullptr;
}

void Player::SetSidekick(Sidekick* newSidekick, int index)
{
	if (index >= 0 && index < 3)
	{
		sidekicks[index] = newSidekick;
	}
	else
	{
		std::cout << "Indice de sidekick invalido" << std::endl;
	}
}

void LoW::Player::Fire()
{
	//checar que el player tiene un IAttacker y entonces llamar a su Fire()
}