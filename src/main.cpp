#include "iostream"
#include "raylib.h"
#include <string>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "GameObject.h"
#include "Player.h"
#include "Sidekick.h"
#include <vector>
#include <UISystem.h>
#include <World.h>

// es válido usarlo porque estamos desarrollando con el namespace de neustro juego
using namespace LoW;

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	std::cout << "Initializing game system " << std::endl;

	// Create the window and OpenGL context
	InitWindow(1280, 800, "Juego con Objetos");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	//cargar el mundo
	World::getInstance();

	// Crear nuestro objeto de prueba
	GameObject* myObj = new GameObject({ 200,200 }, "myObj", LoadTexture("wabbit_alpha.png"));
	myObj->displayName = true;
	// push_back agrega un elemento al final del arreglo
	GameObject::gameObjects.push_back(myObj); // cast implicito a GameObject*

	//El jugador
	Player* playerCharacter = new Player({ 0, 0 }, "Player1"); /*LoadTexture("wabbit_alpha.png"));*/
	playerCharacter->speed = 200;
	GameObject::gameObjects.push_back(static_cast<GameObject*>(playerCharacter));

	//prueba de arma
	Weapon* w = new Weapon({500,500}, "Sword", LoadTexture("sword.png"));
	//playerCharacter->SetWeapon(w); // Asignar el arma al jugador
	GameObject::gameObjects.push_back(w);

	Sidekick* sidekick = new Sidekick({ 500,0 }, "Sidekick", LoadTexture("sidekick.png"));
	sidekick->owner = playerCharacter;
	//playerCharacter->SetSidekick(sidekick, 0);
	sidekick->displayName = true;
	sidekick->speed = 199.0f;
	GameObject::gameObjects.push_back(sidekick);

	Sidekick* sidekick2 = new Sidekick({ 800, 600 }, "Bar", LoadTexture("dogo.png"));
	sidekick2->owner = playerCharacter;
	//playerCharacter->SetSidekick(sidekick2, 1);
	sidekick2->displayName = true;
	sidekick2->speed = 190.0f;
	GameObject::gameObjects.push_back(sidekick2);

	UISystem::getInstance().createImage("Avatar.jpg", 60, 120, 200, 200);


	// Example of dynamic_cast
	for (GameObject* obj : GameObject::gameObjects)
	{
		Player* p = dynamic_cast<Player*>(obj);
		if (p)
		{
			p->attack();
		}
		Sidekick* sk = dynamic_cast<Sidekick*>(obj);
		if (sk != nullptr)
		{
			sk->flee();
		}
	}

	UISystem::getInstance().createButton("Click -> Spawn", 450, 70, 210, 30, 30);

	// Initialize UI elements
	UISystem::getInstance().test(); // probar el singleton de UI
	UISystem::Test(); // probar el método estático del singleton de UI

	UISystem::getInstance().createLabel(TextFormat("No place to hide"), 500, GetScreenHeight()-40, 35);

	// game loop a 60 fps
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//actualizar todos los gameobjects
		for (GameObject* obj : GameObject::gameObjects)
		{
			obj->update();
		}

		UISystem::Update(); // actualizar el sistema de UI

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(DARKBLUE);

		// dibujar el mundo es lo primero que hacemos
		World::getInstance().Draw();

		// draw some text using the default font
		DrawText("Escape from Lost Village", 10,10,64, YELLOW);

		for (GameObject* obj : GameObject::gameObjects)
		{
			obj->draw();
		}

		// arriba de todo dibujamos el sistema de UI
		UISystem::Draw();

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
