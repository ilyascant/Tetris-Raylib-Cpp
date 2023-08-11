#pragma once
#include <raylib.h>
#include <vector>
#include "colors.h"
#include "grid.h"

class Block {
   public:
    Block(Grid& grid)
        : grid(grid){};

    virtual ~Block() = default;

    void DrawBlock() const;
    void DrawPredictBlock(Block block) const;
    void RotateBlock();
    void MoveBlock(int x, int y);
    void ResetBlock();
    bool CanSpawn() const;

    int blockColor = 0;  // stands for DARKBLUE
    int x_block_pos = 3;
    int y_block_pos = 0;

    bool isLocked = false;

   private:
    Grid& grid;
    bool CanMove(int x, int y);
    bool CanRotate() const;

   public:
    std::vector<std::vector<int>> shape;
};