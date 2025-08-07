#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player.h"

typedef enum {
    PROF_MATEMATICAS = 0,
    PROF_FISICA,
    PROF_PROGRAMACION,
    PROF_QUIMICA,
    PROF_DIRECTOR,
    NUM_ENEMY_TYPES
} EnemyType;

typedef enum {
    ENEMY_IDLE,
    ENEMY_PATROL,
    ENEMY_CHASE,
    ENEMY_ATTACK,
    ENEMY_DEAD
} EnemyState;

typedef struct {
    char name[30];
    EnemyType type;
    EnemyState state;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int speed;
    int experience_reward;
    Vector2 position;
    Vector2 startPosition;
    Vector2 target;
    Color color;
    char subject[20];
    float moveTimer;
    float attackTimer;
    bool isAlive;
} Enemy;

// Funciones de creación y gestión de enemigos
Enemy CreateEnemy(EnemyType type, Vector2 position);
void UpdateEnemy(Enemy *enemy, const Player *player);
void DrawEnemy(const Enemy *enemy);

// Funciones de combate
void EnemyTakeDamage(Enemy *enemy, int damage);
int EnemyAttackPlayer(const Enemy *enemy);
bool IsEnemyInRange(const Enemy *enemy, const Player *player, float range);

// Funciones de IA
void EnemyPatrol(Enemy *enemy);
void EnemyChasePlayer(Enemy *enemy, const Player *player);
void EnemyReturnToStart(Enemy *enemy);

// Funciones auxiliares
float DistanceBetween(Vector2 pos1, Vector2 pos2);
Vector2 GetDirectionTo(Vector2 from, Vector2 to);

#endif