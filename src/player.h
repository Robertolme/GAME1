#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

typedef struct {
    char name[20];
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    int experience;
    int level;
    Vector2 position;
    Color color;
    char description[100];
} Player;

typedef enum {
    CHAR_ROBERT = 0,
    CHAR_FRANCO,
    CHAR_COUTENCOS,
    CHAR_FERCHA,
    CHAR_ALDO,
    CHAR_CHEMA,
    NUM_CHARACTERS
} CharacterType;

// Función para crear personajes predefinidos
Player CreateCharacter(CharacterType type);

// Funciones de movimiento y actualización
void UpdatePlayer(Player *player);
void DrawPlayer(const Player *player);
void MovePlayer(Player *player, Vector2 direction);
bool IsPlayerAtPosition(const Player *player, Vector2 position);

// Funciones de combate
void PlayerTakeDamage(Player *player, int damage);
void PlayerGainExperience(Player *player, int exp);
bool IsPlayerAlive(const Player *player);

#endif