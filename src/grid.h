#pragma once
#include <raylib.h>
#include <vector>

class Block;

class Grid {
   private:
    static const int cols = 10;
    static const int rows = 22;  // 2 for invisible layer
    static const int gridSpace = 20;

    std::vector<Color> colors;

   public:
    Grid();
    ~Grid();

   public:
    std::vector<std::vector<int>> grid;
    static const int invisibleLayer = 2;

    void InitGrid();
    void DrawGrid();
    void DrawScoreBoard();
    void LockBlock(Block& block, int x_pos, int y_pos);

    void CheckComboRows();

    static inline int getCols() { return cols; }
    static inline int getRows() { return rows; }
    static inline int getGridSpace() { return gridSpace; }
};