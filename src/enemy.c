#include "enemy.h"
#include "map.h"
#include <string.h>
#include <math.h>

Enemy CreateEnemy(EnemyType type, Vector2 position) {
    Enemy enemy = {0};
    enemy.type = type;
    enemy.state = ENEMY_PATROL;
    enemy.position = position;
    enemy.startPosition = position;
    enemy.target = position;
    enemy.moveTimer = 0.0f;
    enemy.attackTimer = 0.0f;
    enemy.isAlive = true;
    
    switch(type) {
        case PROF_MATEMATICAS:
            strcpy(enemy.name, "Prof. Algebra");
            strcpy(enemy.subject, "Matematicas");
            enemy.health = 80;
            enemy.attack = 12;
            enemy.defense = 8;
            enemy.speed = 8;
            enemy.experience_reward = 25;
            enemy.color = BLUE;
            break;
            
        case PROF_FISICA:
            strcpy(enemy.name, "Prof. Newton");
            strcpy(enemy.subject, "Fisica");
            enemy.health = 100;
            enemy.attack = 15;
            enemy.defense = 10;
            enemy.speed = 6;
            enemy.experience_reward = 30;
            enemy.color = ORANGE;
            break;
            
        case PROF_PROGRAMACION:
            strcpy(enemy.name, "Prof. Code");
            strcpy(enemy.subject, "Programacion");
            enemy.health = 70;
            enemy.attack = 18;
            enemy.defense = 6;
            enemy.speed = 12;
            enemy.experience_reward = 35;
            enemy.color = GREEN;
            break;
            
        case PROF_QUIMICA:
            strcpy(enemy.name, "Prof. Elemento");
            strcpy(enemy.subject, "Quimica");
            enemy.health = 90;
            enemy.attack = 16;
            enemy.defense = 12;
            enemy.speed = 7;
            enemy.experience_reward = 40;
            enemy.color = PURPLE;
            break;
            
        case PROF_DIRECTOR:
            strcpy(enemy.name, "Director");
            strcpy(enemy.subject, "Administracion");
            enemy.health = 200;
            enemy.attack = 25;
            enemy.defense = 20;
            enemy.speed = 5;
            enemy.experience_reward = 100;
            enemy.color = MAROON;
            break;
            
        case NUM_ENEMY_TYPES:
            // Default case - should not happen
            strcpy(enemy.name, "Prof. Unknown");
            strcpy(enemy.subject, "Unknown");
            enemy.health = 50;
            enemy.attack = 10;
            enemy.defense = 5;
            enemy.speed = 5;
            enemy.experience_reward = 10;
            enemy.color = GRAY;
            break;
    }
    
    enemy.maxHealth = enemy.health;
    return enemy;
}

void UpdateEnemy(Enemy *enemy, const Player *player) {
    if (!enemy->isAlive) {
        enemy->state = ENEMY_DEAD;
        return;
    }
    
    enemy->moveTimer += GetFrameTime();
    enemy->attackTimer += GetFrameTime();
    
    float distanceToPlayer = DistanceBetween(enemy->position, player->position);
    
    switch(enemy->state) {
        case ENEMY_IDLE:
            if (enemy->moveTimer >= 2.0f) {
                enemy->state = ENEMY_PATROL;
                enemy->moveTimer = 0.0f;
            }
            break;
            
        case ENEMY_PATROL:
            if (distanceToPlayer <= 5.0f) {
                enemy->state = ENEMY_CHASE;
                enemy->target = player->position;
            } else {
                EnemyPatrol(enemy);
            }
            break;
            
        case ENEMY_CHASE:
            if (distanceToPlayer <= 1.5f) {
                enemy->state = ENEMY_ATTACK;
                enemy->attackTimer = 0.0f;
            } else if (distanceToPlayer > 8.0f) {
                enemy->state = ENEMY_PATROL;
                EnemyReturnToStart(enemy);
            } else {
                EnemyChasePlayer(enemy, player);
            }
            break;
            
        case ENEMY_ATTACK:
            if (distanceToPlayer > 2.0f) {
                enemy->state = ENEMY_CHASE;
            }
            break;
            
        case ENEMY_DEAD:
            // No hacer nada, el enemigo está muerto
            break;
    }
}

void DrawEnemy(const Enemy *enemy) {
    if (!enemy->isAlive) return;
    
    Vector2 screenPos = {
        enemy->position.x * TILE_SIZE,
        enemy->position.y * TILE_SIZE
    };
    
    // Dibujar rectángulo representando al profesor
    DrawRectangle((int)screenPos.x + 2, (int)screenPos.y + 2, TILE_SIZE - 4, TILE_SIZE - 4, enemy->color);
    DrawRectangleLines((int)screenPos.x + 2, (int)screenPos.y + 2, TILE_SIZE - 4, TILE_SIZE - 4, BLACK);
    
    // Dibujar nombre del profesor
    DrawText(enemy->name, (int)screenPos.x - 15, (int)screenPos.y - 20, 8, BLACK);
    
    // Barra de vida
    int barWidth = TILE_SIZE + 5;
    int barHeight = 3;
    float healthRatio = (float)enemy->health / (float)enemy->maxHealth;
    
    DrawRectangle((int)screenPos.x - 2, (int)screenPos.y + TILE_SIZE + 1, barWidth, barHeight, RED);
    DrawRectangle((int)screenPos.x - 2, (int)screenPos.y + TILE_SIZE + 1, (int)(barWidth * healthRatio), barHeight, GREEN);
    
    // Indicador de estado
    Color stateColor = WHITE;
    switch(enemy->state) {
        case ENEMY_IDLE: stateColor = GRAY; break;
        case ENEMY_PATROL: stateColor = YELLOW; break;
        case ENEMY_CHASE: stateColor = ORANGE; break;
        case ENEMY_ATTACK: stateColor = RED; break;
        case ENEMY_DEAD: stateColor = DARKGRAY; break;
    }
    DrawCircle((int)screenPos.x + TILE_SIZE - 3, (int)screenPos.y + 3, 2, stateColor);
}

void EnemyTakeDamage(Enemy *enemy, int damage) {
    int actualDamage = damage - enemy->defense/2;
    if (actualDamage < 1) actualDamage = 1;
    
    enemy->health -= actualDamage;
    if (enemy->health <= 0) {
        enemy->health = 0;
        enemy->isAlive = false;
    }
}

int EnemyAttackPlayer(const Enemy *enemy) {
    if (enemy->attackTimer >= 1.0f) { // Ataque cada segundo
        return enemy->attack;
    }
    return 0;
}

bool IsEnemyInRange(const Enemy *enemy, const Player *player, float range) {
    return DistanceBetween(enemy->position, player->position) <= range;
}

void EnemyPatrol(Enemy *enemy) {
    if (enemy->moveTimer >= 1.0f) {
        // Movimiento aleatorio limitado alrededor de la posición inicial
        Vector2 newTarget = enemy->startPosition;
        newTarget.x += (GetRandomValue(-3, 3));
        newTarget.y += (GetRandomValue(-3, 3));
        
        // Asegurar que esté dentro de los límites del mapa
        if (newTarget.x >= 0 && newTarget.x < MAP_WIDTH && 
            newTarget.y >= 0 && newTarget.y < MAP_HEIGHT) {
            enemy->target = newTarget;
        }
        
        // Mover hacia el objetivo
        Vector2 direction = GetDirectionTo(enemy->position, enemy->target);
        enemy->position.x += direction.x * 0.5f;
        enemy->position.y += direction.y * 0.5f;
        
        enemy->moveTimer = 0.0f;
    }
}

void EnemyChasePlayer(Enemy *enemy, const Player *player) {
    if (enemy->moveTimer >= 0.3f) {
        Vector2 direction = GetDirectionTo(enemy->position, player->position);
        enemy->position.x += direction.x * 0.8f;
        enemy->position.y += direction.y * 0.8f;
        enemy->moveTimer = 0.0f;
    }
}

void EnemyReturnToStart(Enemy *enemy) {
    Vector2 direction = GetDirectionTo(enemy->position, enemy->startPosition);
    enemy->position.x += direction.x * 0.3f;
    enemy->position.y += direction.y * 0.3f;
    
    if (DistanceBetween(enemy->position, enemy->startPosition) <= 1.0f) {
        enemy->position = enemy->startPosition;
        enemy->state = ENEMY_IDLE;
    }
}

float DistanceBetween(Vector2 pos1, Vector2 pos2) {
    float dx = pos1.x - pos2.x;
    float dy = pos1.y - pos2.y;
    return sqrtf(dx * dx + dy * dy);
}

Vector2 GetDirectionTo(Vector2 from, Vector2 to) {
    Vector2 direction = {to.x - from.x, to.y - from.y};
    float length = sqrtf(direction.x * direction.x + direction.y * direction.y);
    
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }
    
    return direction;
}