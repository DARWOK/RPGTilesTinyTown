#pragma once
#include "raylib.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <cstdio>

#define TILE_SIZE 64
#define TILEMAPX 16
#define TILEMAPY 12
#define MAX_TILES 132
#define MAP_TILES (TILEMAPX * TILEMAPY)

namespace LoW {
    class World {
    public:
        static World* instance;
        size_t* tilemap = nullptr;
        Texture tiles[MAP_TILES]{};

        static World& getInstance() {
            static World instance;
            return instance;
        }

        void InitWorld(const char* mapFile) {
            LoadTiles("tinytown/Tiles");
            LoadMap(mapFile);
        }

        void Draw() {
            for (size_t y = 0; y < TILEMAPY; y++) {
                for (size_t x = 0; x < TILEMAPX; x++) {
                    size_t idx = y * TILEMAPX + x;


                    // ======= INICIO BUG INTENCIONAL =======
                    size_t tileId = tilemap[idx] + 100; // BUG: desplazamos el id artificialmente
					// ======= FIN BUG INTENCIONAL =======
                    std::cout << "[Draw] x=" << x
                        << " y=" << y
                        << " idx=" << idx
                        << " baseId=" << tilemap[idx]
                        << " tileId(shifted)=" << tileId
                        << " MAX_TILES=" << MAX_TILES
                        << std::endl;
                    if (tileId >= MAX_TILES) {
                        throw std::out_of_range("tileId fuera de rango en World::Draw()");
                    }

                    Texture2D& tex = tiles[tileId]; // ya es seguro


					// Solución al bug intencional =================

                    // Paso 5B) validación de rango
                    /*if (tileId >= MAX_TILES) {
                        std::cerr << "[ERROR] tileId=" << tileId
                            << " fuera de [0," << (MAX_TILES - 1) << "] "
                            << " en (" << x << "," << y << ")\n";
                        throw std::out_of_range("tileId fuera de rango en World::Draw()");
                    }*/

                    // acceso seguro
                    Texture2D& tex = tiles[tileId];
					// ========================


                    //DrawTexture(tiles[tilemap[idx]], static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), WHITE);
                    DrawTexture(tiles[tilemap[tileId]], static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), WHITE);
                }
            }
        }

        ~World() {
            for (auto& t : tiles)
                if (t.id) UnloadTexture(t);
            delete[] tilemap;
        }

    private:
        World() = default;
        World(const World&) = delete;
        World& operator=(const World&) = delete;
        //float tileScale = TILE_SIZE / tiles[0].width;
        void LoadTiles(const std::string& dir) {
            char path[256];
            for (size_t i = 0; i < MAX_TILES; i++) {
                std::snprintf(path, sizeof(path), "%s/tile_%04zu.png", dir.c_str(), i);
                if (!std::filesystem::exists(path))
                    throw std::runtime_error("Tile no encontrada");

                Image img = LoadImage(path);
                if (!img.data)
                    throw std::runtime_error("Tile no encontrada");

                tiles[i] = LoadTextureFromImage(img);
                UnloadImage(img);
            }
        }

        void LoadMap(const std::string& file) {
            if (!std::filesystem::exists(file))
                throw std::runtime_error("Mapa no encontrado");

            std::ifstream in(file);
            if (!in)
                throw std::runtime_error("Mapa no encontrado");

            tilemap = new size_t[MAP_TILES];
            for (size_t i = 0; i < MAP_TILES; i++) {
                if (!(in >> tilemap[i]) || tilemap[i] >= MAX_TILES)
                    throw std::runtime_error("Mapa malformado");
            }
            // Si hay datos extra después del mapa
            size_t extra;
            if (in >> extra)
                throw std::runtime_error("Mapa malformado");
        }
    };
}