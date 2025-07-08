#include "map.h"

int main() {
    InitWindow(MAP_WIDTH*TILE_SIZE, MAP_HEIGHT*TILE_SIZE, "RPG Universidad - Mapa");
    Map mapa = InitMap();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawMap(&mapa);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
