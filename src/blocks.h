#pragma once
#include <vector>
#include "block.h"
#include "colors.h"
#include "grid.h"

namespace Blocks {

class LBlock : public Block {
   public:
    LBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{1, 0},
                       {1, 0},
                       {1, 1}};
        this->blockColor = 3;
    }
};
class IBlock : public Block {
   public:
    IBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{1},
                       {1},
                       {1},
                       {1}};
        this->blockColor = 6;
    }
};
class SBlock : public Block {
   public:
    SBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{0, 1, 1},
                       {1, 1, 0}};
        this->blockColor = 2;
    }
};
class ZBlock : public Block {
   public:
    ZBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{1, 1, 0},
                       {0, 1, 1}};
        this->blockColor = 1;
    }
};
class JBlock : public Block {
   public:
    JBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{0, 1},
                       {0, 1},
                       {1, 1}};

        this->blockColor = 7;
    }
};
class TBlock : public Block {
   public:
    TBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{1, 1, 1},
                       {0, 1, 0}};
        this->blockColor = 5;
    }
};
class OBlock : public Block {
   public:
    OBlock(Grid& grid)
        : Block(grid) {
        this->shape = {{1, 1},
                       {1, 1}}

        ;
        this->blockColor = 4;
    }
};

}  // namespace Blocks