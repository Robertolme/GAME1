#include "game.h"
#include <string.h>
#include <stdio.h>

Game InitGame() {
    Game game = {0};
    game.state = GAME_CHARACTER_SELECT;
    game.gameMap = InitMap();
    game.selectedCharacter = 0;
    game.inCombat = false;
    game.combatEnemy = NULL;
    game.combatTimer = 0.0f;
    game.enemyCount = 0;
    game.messageTimer = 0.0f;
    
    InitEnemies(&game);
    
    return game;
}

void InitEnemies(Game *game) {
    game->enemyCount = 5;
    
    // Colocar profesores en diferentes partes del mapa
    game->enemies[0] = CreateEnemy(PROF_MATEMATICAS, (Vector2){15, 10});
    game->enemies[1] = CreateEnemy(PROF_FISICA, (Vector2){25, 15});
    game->enemies[2] = CreateEnemy(PROF_PROGRAMACION, (Vector2){10, 25});
    game->enemies[3] = CreateEnemy(PROF_QUIMICA, (Vector2){35, 20});
    game->enemies[4] = CreateEnemy(PROF_DIRECTOR, (Vector2){30, 30});
}

void UpdateMenu(Game *game) {
    if (IsKeyPressed(KEY_ENTER)) {
        game->state = GAME_CHARACTER_SELECT;
    }
}

void UpdateCharacterSelect(Game *game) {
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
        game->selectedCharacter = (game->selectedCharacter - 1 + NUM_CHARACTERS) % NUM_CHARACTERS;
    }
    
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
        game->selectedCharacter = (game->selectedCharacter + 1) % NUM_CHARACTERS;
    }
    
    if (IsKeyPressed(KEY_ENTER)) {
        game->selectedPlayer = CreateCharacter((CharacterType)game->selectedCharacter);
        game->state = GAME_PLAYING;
        ShowMessage(game, "¡Comienza la aventura! Usa WASD para moverte.", 3.0f);
    }
}

void UpdatePlaying(Game *game) {
    UpdatePlayer(&game->selectedPlayer);
    
    // Actualizar enemigos
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].isAlive) {
            UpdateEnemy(&game->enemies[i], &game->selectedPlayer);
        }
    }
    
    CheckCollisions(game);
    
    // Actualizar timer de mensaje
    if (game->messageTimer > 0) {
        game->messageTimer -= GetFrameTime();
    }
    
    // Verificar condición de victoria (todos los enemigos derrotados)
    bool allEnemiesDefeated = true;
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].isAlive) {
            allEnemiesDefeated = false;
            break;
        }
    }
    
    if (allEnemiesDefeated) {
        game->state = GAME_VICTORY;
    }
    
    // Verificar game over
    if (!IsPlayerAlive(&game->selectedPlayer)) {
        game->state = GAME_GAME_OVER;
    }
}

void UpdateCombat(Game *game) {
    game->combatTimer += GetFrameTime();
    
    if (IsKeyPressed(KEY_SPACE)) {
        // Jugador ataca
        if (game->combatEnemy && game->combatEnemy->isAlive) {
            EnemyTakeDamage(game->combatEnemy, game->selectedPlayer.attack);
            
            if (!game->combatEnemy->isAlive) {
                PlayerGainExperience(&game->selectedPlayer, game->combatEnemy->experience_reward);
                ShowMessage(game, "¡Enemigo derrotado! Ganaste experiencia.", 2.0f);
                EndCombat(game);
                return;
            }
        }
    }
    
    // Enemigo ataca automáticamente
    if (game->combatTimer >= 2.0f && game->combatEnemy && game->combatEnemy->isAlive) {
        int damage = EnemyAttackPlayer(game->combatEnemy);
        if (damage > 0) {
            PlayerTakeDamage(&game->selectedPlayer, damage);
            game->combatTimer = 0.0f;
            
            if (!IsPlayerAlive(&game->selectedPlayer)) {
                game->state = GAME_GAME_OVER;
                return;
            }
        }
    }
    
    if (IsKeyPressed(KEY_ESCAPE)) {
        EndCombat(game);
    }
}

void DrawMenu(const Game *game) {
    ClearBackground(DARKBLUE);
    
    DrawText("RPG UNIVERSIDAD", MAP_WIDTH*TILE_SIZE/2 - 120, MAP_HEIGHT*TILE_SIZE/2 - 100, 30, WHITE);
    DrawText("Presiona ENTER para comenzar", MAP_WIDTH*TILE_SIZE/2 - 150, MAP_HEIGHT*TILE_SIZE/2 - 50, 20, LIGHTGRAY);
}

void DrawCharacterSelect(const Game *game) {
    ClearBackground(DARKGREEN);
    
    DrawText("SELECCIONA TU PERSONAJE", MAP_WIDTH*TILE_SIZE/2 - 150, 50, 25, WHITE);
    DrawText("Usa las flechas <- -> para navegar, ENTER para seleccionar", MAP_WIDTH*TILE_SIZE/2 - 200, 80, 15, LIGHTGRAY);
    
    // Dibujar personajes
    int startX = 100;
    int spacing = 120;
    
    for (int i = 0; i < NUM_CHARACTERS; i++) {
        Player character = CreateCharacter((CharacterType)i);
        int x = startX + i * spacing;
        int y = 150;
        
        // Highlight del personaje seleccionado
        if (i == game->selectedCharacter) {
            DrawRectangle(x - 10, y - 10, 100, 200, YELLOW);
        }
        
        // Dibujar representación del personaje
        DrawCircle(x + 30, y + 30, 25, character.color);
        DrawCircleLines(x + 30, y + 30, 25, BLACK);
        
        // Información del personaje
        DrawText(character.name, x, y + 70, 15, BLACK);
        DrawText(TextFormat("Vida: %d", character.health), x, y + 90, 12, DARKGRAY);
        DrawText(TextFormat("Ataque: %d", character.attack), x, y + 105, 12, DARKGRAY);
        DrawText(TextFormat("Defensa: %d", character.defense), x, y + 120, 12, DARKGRAY);
        DrawText(TextFormat("Velocidad: %d", character.speed), x, y + 135, 12, DARKGRAY);
        
        // Descripción (primera línea)
        char desc[50];
        strncpy(desc, character.description, 49);
        desc[49] = '\0';
        DrawText(desc, x - 10, y + 160, 10, DARKBLUE);
    }
}

void DrawPlaying(const Game *game) {
    ClearBackground(BLACK);
    
    // Dibujar mapa
    DrawMap(&game->gameMap);
    
    // Dibujar enemigos
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].isAlive) {
            DrawEnemy(&game->enemies[i]);
        }
    }
    
    // Dibujar jugador
    DrawPlayer(&game->selectedPlayer);
    
    // Dibujar HUD
    DrawHUD(game);
    
    // Mostrar mensaje si hay uno
    if (game->messageTimer > 0) {
        DrawText(game->message, 10, MAP_HEIGHT*TILE_SIZE - 30, 15, YELLOW);
    }
}

void DrawCombat(const Game *game) {
    // Fondo de combate
    DrawRectangle(0, 0, MAP_WIDTH*TILE_SIZE, MAP_HEIGHT*TILE_SIZE, Fade(BLACK, 0.8f));
    
    int centerX = MAP_WIDTH*TILE_SIZE/2;
    int centerY = MAP_HEIGHT*TILE_SIZE/2;
    
    DrawText("¡COMBATE!", centerX - 80, centerY - 150, 30, RED);
    
    if (game->combatEnemy) {
        // Información del enemigo
        DrawText(game->combatEnemy->name, centerX - 100, centerY - 100, 20, WHITE);
        DrawText(TextFormat("Vida: %d/%d", game->combatEnemy->health, game->combatEnemy->maxHealth), 
                centerX - 100, centerY - 70, 15, RED);
        
        // Información del jugador
        DrawText(game->selectedPlayer.name, centerX - 100, centerY + 20, 20, WHITE);
        DrawText(TextFormat("Vida: %d/%d", game->selectedPlayer.health, game->selectedPlayer.maxHealth), 
                centerX - 100, centerY + 50, 15, GREEN);
    }
    
    DrawText("Presiona ESPACIO para atacar", centerX - 120, centerY + 100, 15, YELLOW);
    DrawText("Presiona ESC para huir", centerX - 90, centerY + 120, 15, GRAY);
}

void DrawHUD(const Game *game) {
    // Panel de información del jugador
    DrawRectangle(10, 10, 200, 80, Fade(BLACK, 0.7f));
    DrawRectangleLines(10, 10, 200, 80, WHITE);
    
    DrawText(game->selectedPlayer.name, 15, 15, 15, WHITE);
    DrawText(TextFormat("Nivel: %d", game->selectedPlayer.level), 15, 35, 12, YELLOW);
    DrawText(TextFormat("Vida: %d/%d", game->selectedPlayer.health, game->selectedPlayer.maxHealth), 15, 50, 12, GREEN);
    DrawText(TextFormat("Exp: %d", game->selectedPlayer.experience), 15, 65, 12, BLUE);
    
    // Controles
    DrawText("WASD: Moverse", MAP_WIDTH*TILE_SIZE - 120, 10, 12, LIGHTGRAY);
}

void StartCombat(Game *game, Enemy *enemy) {
    game->state = GAME_COMBAT;
    game->inCombat = true;
    game->combatEnemy = enemy;
    game->combatTimer = 0.0f;
}

void EndCombat(Game *game) {
    game->state = GAME_PLAYING;
    game->inCombat = false;
    game->combatEnemy = NULL;
    game->combatTimer = 0.0f;
}

void CheckCollisions(Game *game) {
    for (int i = 0; i < game->enemyCount; i++) {
        if (game->enemies[i].isAlive && 
            DistanceBetween(game->selectedPlayer.position, game->enemies[i].position) <= 1.5f) {
            StartCombat(game, &game->enemies[i]);
            break;
        }
    }
}

void ShowMessage(Game *game, const char* text, float duration) {
    strncpy(game->message, text, sizeof(game->message) - 1);
    game->message[sizeof(game->message) - 1] = '\0';
    game->messageTimer = duration;
}