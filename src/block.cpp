#include "block.h"
#include <iostream>
#include "colors.h"
#include "game.h"
#include "grid.h"

void Block::DrawBlock() const {
    for (int row = 0; row < (int)shape.size(); row++) {
        for (int col = 0; col < (int)shape[row].size(); col++) {
            if (shape[row][col] == 1)
                DrawRectangle((x_block_pos + col) * Grid::getGridSpace() + 1, (y_block_pos + row) * Grid::getGridSpace() + 1, Grid::getGridSpace() - 1, Grid::getGridSpace() - 1, Colors::GetCellColors()[blockColor]);
        }
    }
}

void Block::DrawPredictBlock(Block block) const {
    bool exitLoop = false;

    while (!exitLoop) {
        block.y_block_pos += 1;
        for (int row = 0; row < (int)block.shape.size(); row++) {
            for (int col = 0; col < (int)block.shape[row].size(); col++) {
                if (shape[row][col] == 1) {
                    if (block.y_block_pos + row >= Grid::getRows()) {
                        block.y_block_pos -= 1;
                        exitLoop = true;
                        break;
                    } else if (grid.grid[block.y_block_pos + row][block.x_block_pos + col] != 0) {
                        block.y_block_pos -= 1;
                        exitLoop = true;
                        break;
                    }
                }
            }
            if (exitLoop)
                break;
        }
    }
    for (int row = 0; row < (int)block.shape.size(); row++) {
        for (int col = 0; col < (int)block.shape[row].size(); col++) {
            if (block.shape[row][col] == 1)
                DrawRectangleLines((block.x_block_pos + col) * Grid::getGridSpace() + 1, (block.y_block_pos + row) * Grid::getGridSpace() + 1, Grid::getGridSpace() - 1, Grid::getGridSpace() - 1, WHITE);
        }
    }
}

bool Block::CanRotate() const {
    bool canRotate = true;
    for (int row = 0; row < (int)shape.size(); row++) {
        for (int col = 0; col < (int)shape[row].size(); col++) {
            if (shape[row][col] == 1) {
                if (grid.grid[y_block_pos + row][col + x_block_pos] != 0) {
                    return canRotate = false;
                }
            }
        }
    }
    return canRotate;
}

bool Block::CanSpawn() const {
    bool canSpawn = true;
    for (int row = 0; row < (int)shape.size(); row++) {
        for (int col = 0; col < (int)shape[row].size(); col++) {
            if (shape[row][col] == 1) {
                if (grid.grid[y_block_pos + row][col + x_block_pos] != 0) {
                    return canSpawn = false;
                }
            }
        }
    }
    return canSpawn;
}

void Block::RotateBlock() {
    std::vector<std::vector<int>> lastShape(shape);

    // Transpose the matrix
    std::vector<std::vector<int>> transposedShape(shape[0].size(), std::vector<int>(shape.size()));
    for (int row = 0; row < (int)shape.size(); row++) {
        for (int col = 0; col < (int)shape[row].size(); col++) {
            transposedShape[col][row] = shape[row][col];
        }
    }

    shape = transposedShape;
    shape = std::vector<std::vector<int>>(shape.rbegin(), shape.rend());

    if (!CanRotate()) {
        shape = lastShape;
    }
}

bool Block::CanMove(int x, int y) {
    for (int row = 0; row < (int)shape.size(); row++) {
        for (int col = 0; col < (int)shape[row].size(); col++) {
            if (shape[row][col] == 1) {
                if (y_block_pos + row >= Grid::getRows()) {
                    grid.LockBlock(*this, x_block_pos, y_block_pos - y);
                    return false;
                } else if (grid.grid[y_block_pos + row][x_block_pos + col] != 0) {
                    if (x == 0)
                        grid.LockBlock(*this, x_block_pos - x, y_block_pos - y);
                    return false;
                } else if (x_block_pos >= Grid::getCols() || x_block_pos < 0) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Block::MoveBlock(int x, int y) {
    x_block_pos += x;
    y_block_pos += y;
    if (!CanMove(x, y)) {
        x_block_pos -= x;
        y_block_pos -= y;
    }
}

void Block::ResetBlock() {
    x_block_pos = 3;
    y_block_pos = 0;
    isLocked = false;
}
