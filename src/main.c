#include "map.h"
#include "player.h"

int main() {
    InitWindow(MAP_WIDTH*TILE_SIZE, MAP_HEIGHT*TILE_SIZE, "RPG Universidad - Mapa");
    SetTargetFPS(60);

    Map mapa = InitMap();
    Player player = InitPlayer((Vector2){ 100, 100 });

    while (!WindowShouldClose()) {
        UpdatePlayer(&player); // 👈 movimiento

        BeginDrawing();
        ClearBackground(BLACK);
        DrawMap(&mapa);
        DrawPlayer(&player);   // 👈 render
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
