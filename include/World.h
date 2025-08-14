#pragma once
#include "raylib.h"
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <cstdio>

#define TILE_SIZE 64
#define TILEMAPX 16
#define TILEMAPY 12
#define MAX_TILES (TILEMAPX * TILEMAPY)

namespace LoW {
    class World {
    public:
        static World* instance;
        size_t* tilemap = nullptr;
        Texture tiles[MAX_TILES]{};

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
                    DrawTexture(tiles[tilemap[idx]], static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), WHITE);
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

            tilemap = new size_t[MAX_TILES];
            for (size_t i = 0; i < MAX_TILES; i++) {
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
