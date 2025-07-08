#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    Vector2 position;  // Posición en píxeles (o puedes tratarlo como tiles si quieres)
    Color color;       // Color del jugador
    float speed;       // Velocidad de movimiento en píxeles/segundo
} Player;

// Inicializa un jugador con una posición inicial
Player InitPlayer(Vector2 startPos);

// Actualiza el estado del jugador (input/movimiento)
void UpdatePlayer(Player *player);

// Dibuja al jugador en pantalla
void DrawPlayer(Player *player);

#endif
