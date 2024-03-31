#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
    Game();
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;

private:
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);
    bool BlockFits();
    bool IsBlockOutside();
    Grid grid;
    std::vector<Block> blocks;
    Block currBlock;
    Block nextBlock;
    Sound clearSound;
    std::vector<Sound> stackSounds;
};