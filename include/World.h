#pragma once
#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>

#define TILE_SIZE 64
#define TILEMAPX 16
#define TILEMAPY 12
#define MAX_TILES (TILEMAPX * TILEMAPY)

namespace LoW
{
	class World
	{
	private:
		static World* instance; // Singleton instancia
		World() = default; // Constructor privado para evitar instanciación externa
		World(const World&) = delete; // Eliminar el constructor de copia
		World& operator=(const World&) = delete; // Eliminar el operador de asignación

	public:
		//Texture background;
		//Texture collisionMask;
		//Image collisionMaskImg;
		//float tileScale = TILE_SIZE / tiles[0].width;

		size_t* tilemap;
		Texture tiles[MAX_TILES];

		static World& getInstance()
		{
			if (!instance)
			{
				instance = new World();
				instance->InitWorld("map.txt"); // Inicializar el mundo predeterminado
			}
			return *instance;
		}

		//cargar mundo default
		void InitWorld(const char* filename)
		{
			//background = LoadTexture("world1.jpg");
			////collisionMask = LoadTexture("world1_mask.png");
			//collisionMaskImg = LoadImage("world1_mask.png");
			////para que cada byte represente un pixel en escala de grises
			//ImageFormat(&collisionMaskImg, PIXELFORMAT_UNCOMPRESSED_GRAYSCALE);
			char buffer[32];
			for (size_t i = 0; i < MAX_TILES; i++)
			{
				sprintf(buffer, "tinytown/Tiles/tile_%04zu.png", i);
				tiles[i] = LoadTexture(buffer);
			}

			tilemap = new size_t[MAX_TILES];
			std::string workingDir = GetWorkingDirectory();
			std::ifstream file(workingDir + filename);
			if (file.is_open())
			{
				for (size_t y = 0; y <TILEMAPY; y++)
				{
					for (size_t x = 0; x < TILEMAPX; x++)
					{
						//std::string value;
						//std::getline(file, value, ','); // Leer hasta la coma
						//std::cout << "Valor leido: " << value << std::endl;
						std::string value;
						std::getline(file, value, ',');
						size_t index = y * TILEMAPX + x;
						tilemap[index] = std::stoi(value);
					}
				}
			}
			else
			{
				std::cout << "Error: No se pudo abrir el archivo " << filename << std::endl;
			}
		}

		void Draw()
		{
			//DrawTexture(background, 0, 0, WHITE);
			for (size_t y = 0; y < TILEMAPY; y++)
			{
				for (size_t x = 0; x < TILEMAPX; x++)
				{
					size_t index = y * TILEMAPX + x;
					size_t tileID = tilemap[index];

					if (tileID < MAX_TILES)
					{
						DrawTexture(tiles[tileID], x * TILE_SIZE, y * TILE_SIZE, WHITE);
					}
				}
			}

		}

		//checa si el pixel en la posicion point tiene bloqueo
		//bool CheckCollision(Vector2 point)
		//{
		//	//acceder al pixel en particular
		//	int index = (point.y * collisionMaskImg.width + point.x);

		//	char* imgdata = (char*)collisionMaskImg.data; //acceder a los datos de la imagen

		//	std::cout << "valor en pixel ( " << point.x << "," << point.y << "): " << (int)imgdata[index] << std::endl;

		//	return (imgdata[index] != 0); // si el valor es menor a 128, no hay colision

		//}
	};
}



