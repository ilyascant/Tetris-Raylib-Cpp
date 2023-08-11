#include "game.h"
#include <algorithm>
#include <cstring>
#include <iostream>
#include "blocks.h"

int Game::points = 0;

Game::Game()
    : grid(Grid()),
      lastFallTime(GetTime()),
      deltaTime(GetTime()) {
    InitWindow(windowWidth, windowHeight, "TETRIS");

    allBlocks = {
        new Blocks::LBlock(grid),
        new Blocks::IBlock(grid),
        new Blocks::SBlock(grid),
        new Blocks::ZBlock(grid),
        new Blocks::JBlock(grid),
        new Blocks::TBlock(grid),
        new Blocks::OBlock(grid)};

    currentBlock = allBlocks[GetRandomValue(0, 6)];
}

void Game::HandleInput() {
    int pressedKey = GetKeyPressed();

    if (pressedKey == KEY_R) {
        grid.InitGrid();
        currentBlock->ResetBlock();
        currentBlock = allBlocks[GetRandomValue(0, 6)];
        Game::points = 0;
        status = PLAYING;
    }
    if (pressedKey == KEY_P) {
        if (CanTriggerEvent(.1f, deltaTime)) {
            if (status == PAUSED)
                status = PLAYING;
            else
                status = PAUSED;
        }
    }
    if (pressedKey == KEY_UP) {
        currentBlock->RotateBlock();
    }
    if (pressedKey == KEY_RIGHT || IsKeyDown(KEY_RIGHT)) {
        if (CanTriggerEvent(.1f, deltaTime))
            currentBlock->MoveBlock(1, 0);
    }
    if (pressedKey == KEY_LEFT || IsKeyDown(KEY_LEFT)) {
        if (CanTriggerEvent(.1f, deltaTime))
            currentBlock->MoveBlock(-1, 0);
    }
    if (IsKeyDown(KEY_DOWN)) {
        fallingSpeed = std::max(std::min(fallingSpeed - speedIncrement, minSpeed), maxSpeed);
    } else {
        fallingSpeed = .5f;
    }
}

void Game::CheckCollision() {
    if (currentBlock->isLocked) {
        currentBlock->ResetBlock();
        currentBlock = allBlocks[GetRandomValue(0, 6)];
        if (!currentBlock->CanSpawn()) {
            status = GAME_OVER;
            return;
        }
        Game::points += 25;
    }
}

void Game::AdjustText(const char message[], int& textWidth, int& fontSize) {
    textWidth = MeasureText(message, fontSize);
    while (textWidth > windowWidth - 32) {
        fontSize--;
        textWidth = MeasureText(message, fontSize);
    }
}

void Game::EndScreen(enum status) {
    char message[128];
    int fontSize = 32;
    int textWidth;
    ClearBackground(DARKGRAY);
    if (status == GAME_OVER) {
        strcpy(message, "You Lost");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, windowHeight / 2 - 100, fontSize, DARKBLUE);

        int pastFontSize = fontSize;
        snprintf(message, 128, "%s %d", "Points:", Game::points);
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 2) / 2 - 100, fontSize, DARKBLUE);

        pastFontSize = fontSize;
        strcpy(message, "Press 'R'");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 4) / 2 - 50, fontSize, DARKGREEN);

        pastFontSize = fontSize;
        strcpy(message, "to play Again");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 6) / 2 - 50, fontSize, DARKGREEN);
    } else {
        strcpy(message, "Paused");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, windowHeight / 2 - 100, fontSize, DARKBLUE);

        int pastFontSize = fontSize;
        snprintf(message, 128, "%s %d", "Points:", Game::points);
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 2) / 2 - 100, fontSize, DARKBLUE);

        pastFontSize = fontSize;
        strcpy(message, "Press 'P'");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 4) / 2 - 50, fontSize, DARKGREEN);

        pastFontSize = fontSize;
        strcpy(message, "to Continue");
        AdjustText(message, textWidth, fontSize);
        DrawText(message, (windowWidth - textWidth) / 2, (windowHeight + pastFontSize * 6) / 2 - 50, fontSize, DARKGREEN);
    }
}

void Game::Draw() {
    ClearBackground(DARKGRAY);
    grid.DrawGrid();
    currentBlock->DrawPredictBlock(*currentBlock);
    currentBlock->DrawBlock();
    grid.DrawScoreBoard();
}

void Game::Fall() {
    if (CanTriggerEvent(fallingSpeed, lastFallTime)) {
        currentBlock->MoveBlock(0, 1);
        if (fallingSpeed <= .1f)
            Game::points += 1;
    }
}

void Game::HandleCombo() {
    grid.CheckComboRows();
}

bool Game::CanTriggerEvent(float interval, float& compareTime) {
    if (GetTime() - compareTime >= interval) {
        compareTime = GetTime();
        return true;
    }
    return false;
}

Game::~Game() {
}
