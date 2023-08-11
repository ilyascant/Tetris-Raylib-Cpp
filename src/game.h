#pragma once
#include "block.h"
#include "grid.h"
#include "vector"

class Game {
   public:
    Game();
    ~Game();

    enum status {
        PLAYING,
        PAUSED,
        GAME_OVER,
    };

    void HandleInput();
    void Draw();
    void Fall();
    void HandleCombo();
    bool CanTriggerEvent(float interval, float& compareTime);
    void CheckCollision();
    void AdjustText(const char message[], int& textWidth, int& fontSize);
    void EndScreen(enum status = GAME_OVER);

    Block* currentBlock;
    std::vector<Block*> allBlocks;

    enum status status = PLAYING;
    static int points;

    inline int getWindowWidth() const { return windowWidth; };
    inline int getWindowHeight() const { return windowHeight; };

   private:
    Grid grid;
    float fallingSpeed = .5f;
    const float maxSpeed = .05f;
    const float minSpeed = .5f;
    const float speedIncrement = 0.1f;

    const int windowWidth = Grid::getCols() * Grid::getGridSpace();
    const int windowHeight = (Grid::getRows()) * Grid::getGridSpace();

    float lastFallTime;
    float deltaTime;
};