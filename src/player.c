#include "player.h"
#include "raylib.h"

Player InitPlayer(Vector2 startPos) {
    Player player = {
        .position = startPos,
        .color = BLUE,
        .speed = 100.0f // Píxeles por segundo
    };
    return player;
}

void UpdatePlayer(Player *player) {
    float delta = GetFrameTime();  // Para movimiento independiente del framerate

    if (IsKeyDown(KEY_W)) player->position.y -= player->speed * delta;
    if (IsKeyDown(KEY_S)) player->position.y += player->speed * delta;
    if (IsKeyDown(KEY_A)) player->position.x -= player->speed * delta;
    if (IsKeyDown(KEY_D)) player->position.x += player->speed * delta;
}

void DrawPlayer(Player *player) {
    DrawRectangle((int)player->position.x, (int)player->position.y, 32, 32, player->color);
}
