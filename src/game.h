#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "enemy.h"
#include "map.h"

#define MAX_ENEMIES 10

typedef enum {
    GAME_MENU,
    GAME_CHARACTER_SELECT,
    GAME_PLAYING,
    GAME_COMBAT,
    GAME_GAME_OVER,
    GAME_VICTORY
} GameState;

typedef struct {
    GameState state;
    Player selectedPlayer;
    Enemy enemies[MAX_ENEMIES];
    int enemyCount;
    Map gameMap;
    int selectedCharacter;
    bool inCombat;
    Enemy* combatEnemy;
    float combatTimer;
    char message[100];
    float messageTimer;
} Game;

// Funciones de inicialización
Game InitGame();
void InitEnemies(Game *game);

// Funciones de actualización por estado
void UpdateMenu(Game *game);
void UpdateCharacterSelect(Game *game);
void UpdatePlaying(Game *game);
void UpdateCombat(Game *game);

// Funciones de dibujo por estado
void DrawMenu(const Game *game);
void DrawCharacterSelect(const Game *game);
void DrawPlaying(const Game *game);
void DrawCombat(const Game *game);
void DrawHUD(const Game *game);

// Funciones auxiliares
void StartCombat(Game *game, Enemy *enemy);
void EndCombat(Game *game);
void CheckCollisions(Game *game);
void ShowMessage(Game *game, const char* text, float duration);

#endif