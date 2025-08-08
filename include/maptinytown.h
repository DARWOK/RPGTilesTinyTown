#pragma once

#include <stdio.h>
#include <stdlib.h>

#define TILE_SIZE 64
#define TILEMAPX 16
#define TILEMAPY 12
#define MAX_TILES (TILEMAPX * TILEMAPY)

size_t tilemap[MAX_TILES];

void LoadMapFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < MAX_TILES; i++) {
        if (fscanf(file, "%zu", &tilemap[i]) != 1) {
            printf("Error: Formato incorrecto en %s\n", filename);
            fclose(file);
            exit(1);
        }
    }

    fclose(file);
}