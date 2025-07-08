#ifndef MAP_C
#define MAP_C
#include "raylib.h"

#define MAP_WIDTH  60
#define MAP_HEIGHT 40
#define TILE_SIZE  15

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_DESK,
    TILE_DOOR
} TileType;

typedef struct {
    TileType tiles[MAP_HEIGHT][MAP_WIDTH];
} Map;

// Inicializa el mapa (con valores predefinidos por ahora)
Map InitMap();

// Dibuja el mapa en pantalla
void DrawMap(const Map *map);

// ¿Es el tile sólido? (no se puede caminar)
bool IsSolidTile(TileType tile);

#endif
