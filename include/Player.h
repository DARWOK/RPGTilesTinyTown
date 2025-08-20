#pragma once
#include "GameObject.h"
#include "IAttacker.h"
#include <iostream>
#include "Weapon.h"
#include "Sidekick.h"
#include "Inventory.h"
#include "Label.h"

namespace LoW
{
    enum EAnimDirection
    {
        ANIM_DOWN,
        ANIM_UP,
        ANIM_LEFT,
        ANIM_RIGHT,
        ANIM_IDLE
    };

    struct SAnimData
    {
        int currentFrame;
        int maxFrames;
        // Número de frames que han de pasar para cambiar de frama en el sprite
        int frameCounter;
        int frameSpeed = 10;
        float spriteWidth;
        float spriteHeight;
        EAnimDirection direction;
    };

    class Player :
        public GameObject, public IAttacker
    {
    private:
        //info de su animación
        SAnimData animData;

        //instrumento que le permite atacar
        IAttacker* weapon;

        //refs a sus sidekicks
        Sidekick* sidekicks[3];

        // Show pick up weapon message
        bool shouldPromptForWeapon = false;
        const char* weaponPrompt = "Presiona F para recoger arma";
        Label* weaponLabel_ = nullptr;
        std::string weaponText_;
        void UpdateWeaponLabel_(Weapon* w);

    public:
        Inventory inventory;
        float speed = 10.0f;

        void NextWeapon();

        // Nuevo: recoger arma
        void PickupWeapon(Weapon* w);

        void SetWeaponLabel(Label* lbl);

        //constructor heredado de GameObject
        /*Player(Vector2 pos, std::string _name, Texture tex) :
            GameObject(pos, _name, tex),
            weapon(nullptr),
            sidekicks { nullptr, nullptr, nullptr } {}*/

        Player(Vector2 pos, std::string _name) :
            weapon(nullptr)
            //sidekicks{ nullptr, nullptr, nullptr }
        {
            texture = LoadTexture("boy-r.png");
            animData.spriteHeight = 80;
            animData.spriteWidth = 64;
            animData.frameCounter = 0;
            animData.currentFrame = 0;
            animData.maxFrames = 4;
            animData.frameSpeed = 5;
            name = _name;
            position = pos;
            animData.direction = ANIM_DOWN;
        }

        void update() override;

        void draw() override;

        void attack()
        {
            std::cout << name << "Atacando" << std::endl;
        }
        /*void Fire() override
        {
            std::cout << "fuego!" << std::endl;
        }*/
        void Fire();

        IAttacker* SetWeapon(IAttacker* newWeapon);

        void SetSidekick(Sidekick* newSidekick, int index);

    };
}


