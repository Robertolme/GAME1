#include "game.h"

int main() {
    InitWindow(MAP_WIDTH*TILE_SIZE, MAP_HEIGHT*TILE_SIZE, "RPG Universidad - Aventura Academica");
    SetTargetFPS(60);
    
    Game game = InitGame();
    
    while (!WindowShouldClose()) {
        // Actualizar según el estado del juego
        switch(game.state) {
            case GAME_MENU:
                UpdateMenu(&game);
                break;
            case GAME_CHARACTER_SELECT:
                UpdateCharacterSelect(&game);
                break;
            case GAME_PLAYING:
                UpdatePlaying(&game);
                break;
            case GAME_COMBAT:
                UpdateCombat(&game);
                break;
            case GAME_GAME_OVER:
            case GAME_VICTORY:
                if (IsKeyPressed(KEY_R)) {
                    game = InitGame(); // Reiniciar juego
                }
                break;
        }
        
        BeginDrawing();
        
        // Dibujar según el estado del juego
        switch(game.state) {
            case GAME_MENU:
                DrawMenu(&game);
                break;
            case GAME_CHARACTER_SELECT:
                DrawCharacterSelect(&game);
                break;
            case GAME_PLAYING:
                DrawPlaying(&game);
                break;
            case GAME_COMBAT:
                DrawCombat(&game);
                break;
            case GAME_GAME_OVER:
                ClearBackground(MAROON);
                DrawText("GAME OVER", MAP_WIDTH*TILE_SIZE/2 - 100, MAP_HEIGHT*TILE_SIZE/2 - 50, 30, WHITE);
                DrawText("Presiona R para reiniciar", MAP_WIDTH*TILE_SIZE/2 - 120, MAP_HEIGHT*TILE_SIZE/2, 20, LIGHTGRAY);
                break;
            case GAME_VICTORY:
                ClearBackground(DARKGREEN);
                DrawText("¡VICTORIA!", MAP_WIDTH*TILE_SIZE/2 - 80, MAP_HEIGHT*TILE_SIZE/2 - 50, 30, WHITE);
                DrawText("Has derrotado a todos los profesores", MAP_WIDTH*TILE_SIZE/2 - 150, MAP_HEIGHT*TILE_SIZE/2 - 10, 20, YELLOW);
                DrawText("Presiona R para jugar de nuevo", MAP_WIDTH*TILE_SIZE/2 - 130, MAP_HEIGHT*TILE_SIZE/2 + 20, 15, LIGHTGRAY);
                break;
        }
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
