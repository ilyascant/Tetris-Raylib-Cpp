#include "grid.h"
#include <iostream>
#include "block.h"
#include "colors.h"
#include "game.h"

Grid::Grid() {
    colors = Colors::GetCellColors();
    Grid::InitGrid();
}

Grid::~Grid() {
    for (int row = 0; row < rows; row++) {
        grid[row].clear();
    }
    grid.clear();
}

void Grid::InitGrid() {
    grid.resize(rows, std::vector<int>(cols, 0));
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::DrawGrid() {
    for (int row = invisibleLayer; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            DrawRectangle(col * gridSpace + 1, row * gridSpace + 1, gridSpace - 1, gridSpace - 1, colors[grid[row][col]]);
        }
    }
}

void Grid::DrawScoreBoard() {
    const int windowWidth = cols * gridSpace;

    DrawRectangle(0, 0, windowWidth, 2 * gridSpace, DARKGRAY);

    int bufferSize = 128;
    char message[bufferSize];
    snprintf(message, bufferSize, "%s %d", "Points:", Game::points);
    int fontSize = 16;
    int textWidth = MeasureText(message, fontSize);
    DrawText(message, (windowWidth - textWidth - fontSize / 2), fontSize / 2, fontSize, WHITE);
}

void Grid::LockBlock(Block& block, int x_pos, int y_pos) {
    for (int row = 0; row < (int)block.shape.size(); row++) {
        for (int col = 0; col < (int)block.shape[0].size(); col++) {
            if (block.shape[row][col] == 1) {
                block.isLocked = true;
                grid[y_pos + row][x_pos + col] = block.blockColor;
            }
        }
    }
}

void Grid::CheckComboRows() {
    bool isCombo = true;
    for (int row = rows - 1; row >= 0; row--) {
        for (int col = cols - 1; col >= 0; col--) {
            if (grid[row][col] == 0) {
                isCombo = false;
                break;
            }
        }
        if (isCombo) {
            Game::points += 250;
            grid.erase(grid.begin() + row);
            grid.insert(grid.begin(), std::vector<int>(10, 0));
        }
        isCombo = true;
    }
}
