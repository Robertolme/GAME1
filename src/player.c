#include "player.h"
#include "map.h"
#include <string.h>

Player CreateCharacter(CharacterType type) {
    Player player = {0};
    player.level = 1;
    player.experience = 0;
    player.position = (Vector2){5.0f, 5.0f}; // Posición inicial
    
    switch(type) {
        case CHAR_ROBERT:
            strcpy(player.name, "Robert");
            strcpy(player.description, "Lider del equipo, balanceado en todas las areas");
            player.health = 120;
            player.attack = 15;
            player.defense = 12;
            player.speed = 10;
            player.color = BLUE;
            break;
            
        case CHAR_FRANCO:
            strcpy(player.name, "Franco");
            strcpy(player.description, "Guerrero fuerte, alto ataque y defensa");
            player.health = 150;
            player.attack = 20;
            player.defense = 18;
            player.speed = 6;
            player.color = RED;
            break;
            
        case CHAR_COUTENCOS:
            strcpy(player.name, "Coutencos");
            strcpy(player.description, "Estratega inteligente, ataques especiales");
            player.health = 90;
            player.attack = 18;
            player.defense = 8;
            player.speed = 14;
            player.color = PURPLE;
            break;
            
        case CHAR_FERCHA:
            strcpy(player.name, "Fercha");
            strcpy(player.description, "Explorador rapido, alta velocidad");
            player.health = 100;
            player.attack = 12;
            player.defense = 10;
            player.speed = 18;
            player.color = GREEN;
            break;
            
        case CHAR_ALDO:
            strcpy(player.name, "Aldo");
            strcpy(player.description, "Tanque defensivo, resistente al daño");
            player.health = 180;
            player.attack = 10;
            player.defense = 22;
            player.speed = 4;
            player.color = BROWN;
            break;
            
        case CHAR_CHEMA:
            strcpy(player.name, "Chema");
            strcpy(player.description, "Apoyo tecnico, habilidades especiales");
            player.health = 85;
            player.attack = 14;
            player.defense = 9;
            player.speed = 12;
            player.color = YELLOW;
            break;
        
        case NUM_CHARACTERS:
            // Default case - should not happen
            strcpy(player.name, "Unknown");
            strcpy(player.description, "Personaje desconocido");
            player.health = 100;
            player.attack = 10;
            player.defense = 10;
            player.speed = 10;
            player.color = WHITE;
            break;
    }
    
    player.maxHealth = player.health;
    return player;
}

void UpdatePlayer(Player *player) {
    // Manejo de entrada para movimiento
    Vector2 direction = {0, 0};
    
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y = -1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y = 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x = -1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x = 1;
    
    if (direction.x != 0 || direction.y != 0) {
        MovePlayer(player, direction);
    }
}

void DrawPlayer(const Player *player) {
    Vector2 screenPos = {
        player->position.x * TILE_SIZE,
        player->position.y * TILE_SIZE
    };
    
    // Dibujar círculo representando al jugador
    DrawCircle((int)screenPos.x + TILE_SIZE/2, (int)screenPos.y + TILE_SIZE/2, TILE_SIZE/3, player->color);
    DrawCircleLines((int)screenPos.x + TILE_SIZE/2, (int)screenPos.y + TILE_SIZE/2, TILE_SIZE/3, BLACK);
    
    // Dibujar nombre del personaje
    DrawText(player->name, (int)screenPos.x - 10, (int)screenPos.y - 20, 10, BLACK);
    
    // Barra de vida
    int barWidth = TILE_SIZE + 10;
    int barHeight = 4;
    float healthRatio = (float)player->health / (float)player->maxHealth;
    
    DrawRectangle((int)screenPos.x - 5, (int)screenPos.y + TILE_SIZE + 2, barWidth, barHeight, RED);
    DrawRectangle((int)screenPos.x - 5, (int)screenPos.y + TILE_SIZE + 2, (int)(barWidth * healthRatio), barHeight, GREEN);
}

void MovePlayer(Player *player, Vector2 direction) {
    Vector2 newPos = {
        player->position.x + direction.x,
        player->position.y + direction.y
    };
    
    // Verificar límites del mapa
    if (newPos.x < 0 || newPos.x >= MAP_WIDTH || newPos.y < 0 || newPos.y >= MAP_HEIGHT) {
        return;
    }
    
    // Verificar colisiones con el mapa
    // Esta función necesitaría acceso al mapa actual, por ahora se implementa básica
    player->position = newPos;
}

bool IsPlayerAtPosition(const Player *player, Vector2 position) {
    return (int)player->position.x == (int)position.x && (int)player->position.y == (int)position.y;
}

void PlayerTakeDamage(Player *player, int damage) {
    int actualDamage = damage - player->defense/2;
    if (actualDamage < 1) actualDamage = 1;
    
    player->health -= actualDamage;
    if (player->health < 0) player->health = 0;
}

void PlayerGainExperience(Player *player, int exp) {
    player->experience += exp;
    
    // Subir de nivel cada 100 puntos de experiencia
    while (player->experience >= 100 * player->level) {
        player->experience -= 100 * player->level;
        player->level++;
        
        // Aumentar estadísticas al subir de nivel
        player->maxHealth += 10;
        player->health = player->maxHealth; // Curar al subir de nivel
        player->attack += 2;
        player->defense += 1;
        player->speed += 1;
    }
}

bool IsPlayerAlive(const Player *player) {
    return player->health > 0;
}