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
#include "Toolbox.h"
#include "Singleton.h"
#include "LinkedList.h"

typedef Singleton<Toolbox> Logger;

// es válido usarlo porque estamos desarrollando con el namespace de neustro juego
using namespace LoW;

struct LinkedListNode {
	int data;
	LinkedListNode* next;

	LinkedListNode(int value) : data(value), next(nullptr) {}
};

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

	// Prueba de singleton
	// Queremos que nuestro Toolbox sea un singleton
	// No es necesario hacerlo con new, simplemente llamando al instance se crea la instancia
	Singleton<Toolbox>::instance().id = 100;
	Singleton<Toolbox>::instance().name = "Toolbox Principal";

	Singleton<Toolbox>::instance().Log("Hola desde el singleton");
	Logger::instance().Log("Hola desde el singleton con typedef");

	// Crear e imprimir lista enlazada con los valores: 1995, 1999, 2025
	LinkedListNode* node1 = new LinkedListNode(1995);
	LinkedListNode* node2 = new LinkedListNode(1999);
	LinkedListNode* node3 = new LinkedListNode(2025);

	node1->next = node2;
	node2->next = node3;

	// Imprimir la lista
	LinkedListNode* current = node1;
	std::cout << "Linked List Values: ";
	while (current != nullptr) {
		std::cout << current->data << " -> ";
		current = current->next;
	}
	std::cout << "nullptr" << std::endl;

	// Liberar memoria de la lista enlazada
	delete node1;
	delete node2;
	delete node3;

	LinkedList nameList;
	nameList.append("Ixchel");
	nameList.append("Scian");
	nameList.append("Rivia");

	// Imprimir lista
	nameList.print();

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
