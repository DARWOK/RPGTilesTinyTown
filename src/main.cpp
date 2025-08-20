#include "iostream"
#include "raylib.h"
#include <string>
#include "resource_dir.h"    // utility header for SearchAndSetResourceDir
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

struct LinkedListN {
    int data;
    LinkedListN* next;

    LinkedListN(int value) : data(value), next(nullptr) {}
};

int main()
{
    try
    {
        // Tell the window to use vsync and work on high DPI displays
        SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
        std::cout << "Initializing game system " << std::endl;

        // Create the window and OpenGL context
        InitWindow(1280, 800, "Juego con Objetos");

        // Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
        SearchAndSetResourceDir("resources");

        // cargar el mundo (AHORA SÍ inicializamos)
        World::getInstance().InitWorld("map.txt");  // <<<--- CAMBIO CLAVE

        // Crear nuestro objeto de prueba
        GameObject* myObj = new GameObject({ 200,200 }, "myObj", LoadTexture("wabbit_alpha.png"));
        myObj->displayName = true;
        GameObject::gameObjects.push_back(myObj);

        // El jugador
        Player* playerCharacter = new Player({ 0, 0 }, "Player1");
        playerCharacter->speed = 200;
        GameObject::gameObjects.push_back(static_cast<GameObject*>(playerCharacter));

        // prueba de arma
        Weapon* w = new Weapon({ 500,500 }, "Sword", LoadTexture("sword.png"));
        GameObject::gameObjects.push_back(w);

        Sidekick* sidekick = new Sidekick({ 500,0 }, "Sidekick", LoadTexture("sidekick.png"));
        sidekick->owner = playerCharacter;
        sidekick->displayName = true;
        sidekick->speed = 199.0f;
        GameObject::gameObjects.push_back(sidekick);

        Sidekick* sidekick2 = new Sidekick({ 800, 600 }, "Bar", LoadTexture("dogo.png"));
        sidekick2->owner = playerCharacter;
        sidekick2->displayName = true;
        sidekick2->speed = 190.0f;
        GameObject::gameObjects.push_back(sidekick2);

        UISystem::getInstance().createImage("Avatar.jpg", 60, 120, 200, 200);

        // Example of dynamic_cast
        for (GameObject* obj : GameObject::gameObjects)
        {
            if (Player* p = dynamic_cast<Player*>(obj)) { p->attack(); }
            if (Sidekick* sk = dynamic_cast<Sidekick*>(obj)) { sk->flee(); }
        }

        UISystem::getInstance().createButton("Click -> Spawn", 450, 70, 210, 30, 30);

        // Initialize UI elements
        UISystem::getInstance().test(); // probar el singleton de UI
        UISystem::Test(); // probar el método estático del singleton de UI

        UISystem::getInstance().createLabel(TextFormat("No place to hide"), 500, GetScreenHeight() - 40, 35);

        // Prueba de singleton
        Singleton<Toolbox>::instance().id = 100;
        Singleton<Toolbox>::instance().name = "Toolbox Principal";
        Singleton<Toolbox>::instance().Log("Hola desde el singleton");
        Logger::instance().Log("Hola desde el singleton con typedef");

        // Crear e imprimir lista enlazada con los valores: 1995, 1999, 2025
        LinkedListN* node1 = new LinkedListN(1995);
        LinkedListN* node2 = new LinkedListN(1999);
        LinkedListN* node3 = new LinkedListN(2025);
        node1->next = node2; node2->next = node3;

        LinkedListN* current = node1;
        std::cout << "Linked List Values: ";
        while (current != nullptr) { std::cout << current->data << " -> "; current = current->next; }
        std::cout << "nullptr" << std::endl;
        delete node1; delete node2; delete node3;

        LinkedList nameList;
        nameList.append("Ixchel");
        nameList.append("Scian");
        nameList.append("Rivia");
        nameList.print();

        Label* weaponLabel = UISystem::getInstance().createLabel("Arma: —", 10, 10, 22);
        playerCharacter->SetWeaponLabel(weaponLabel);

        // game loop a 60 fps
        while (!WindowShouldClose())
        {
            // actualizar todos los gameobjects
            for (GameObject* obj : GameObject::gameObjects) { obj->update(); }
            UISystem::Update();

            BeginDrawing();
            ClearBackground(DARKBLUE);

            // dibujar el mundo
            World::getInstance().Draw();

            DrawText("Escape from Lost Village", 10, 10, 64, YELLOW);

            for (GameObject* obj : GameObject::gameObjects) { obj->draw(); }
            UISystem::Draw();
            EndDrawing();
        }

        CloseWindow();
        return 0;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        if (IsWindowReady()) CloseWindow();
        return 1;
    }
}
