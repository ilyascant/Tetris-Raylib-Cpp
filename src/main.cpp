#include <raylib.h>
#include <iostream>
#include "game.h"

int main(void) {
    Game game;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();

        switch (game.status) {
            case game.PLAYING:
                game.Fall();
                game.HandleInput();
                game.CheckCollision();
                game.HandleCombo();
                game.Draw();
                break;
            case game.PAUSED:
                game.EndScreen(game.PAUSED);
                game.HandleInput();
                break;
            case game.GAME_OVER:
                game.EndScreen();
                game.HandleInput();
                break;
            default:
                break;
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}