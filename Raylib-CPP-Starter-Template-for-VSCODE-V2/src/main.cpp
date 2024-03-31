#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval) {
    double currTime = GetTime();
    if (currTime - lastUpdateTime >= interval) {
        lastUpdateTime = currTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "Tetris");
    SetTargetFPS(60);
    
    Font font = LoadFontEx("Font/Tetris.tff", 64, 0, 0);
    Game game = Game();

    while (!WindowShouldClose()) {
        game.HandleInput();
        if (EventTriggered(0.5)) {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        DrawTextEx(font, "SCORE", {350, 20}, 38, 2, WHITE);
        DrawTextEx(font, "NEXT", {355, 180}, 38, 2, WHITE);
        if (game.gameOver) {
            DrawTextEx(font, "GAME", {350, 460}, 38, 2, WHITE);
            DrawTextEx(font, "OVER", {350, 500}, 38, 2, WHITE);
        }
        DrawRectangleRounded({320, 60, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 75}, 38, 2, WHITE);
        DrawRectangleRounded({320, 220, 170, 170}, 0.3, 6, lightBlue);

        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}