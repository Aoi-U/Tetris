#include "game.h"
#include <random>

Game::Game() {
    grid = Grid();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    clearSound = LoadSound("Sounds/RowCleared.wav");
    stackSounds.resize(4);
    stackSounds[0] = LoadSound("Sounds/Stack1.wav");
    stackSounds[1] = LoadSound("Sounds/Stack2.wav");
    stackSounds[2] = LoadSound("Sounds/Stack3.wav");
    stackSounds[3] = LoadSound("Sounds/Stack4.wav");
}

Game::~Game() {
    UnloadSound(AUGH);
    UnloadSound(clearSound);
    for (int i = 0; i < (int)stackSounds.size(); i++) {
        UnloadSound(stackSounds[i]);
    }
    CloseAudioDevice();
}

Block Game::GetRandomBlock() {
    if (blocks.empty()) {
        blocks = GetAllBlocks();
    }

    int randIndex = rand() % blocks.size();
    Block block = blocks[randIndex];
    blocks.erase(blocks.begin() + randIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks() {
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw() {
    grid.Draw();
    currBlock.Draw(11, 11);
    switch (nextBlock.id) {
        case 3: 
            nextBlock.Draw(255, 290);
            break;
        case 4:
            nextBlock.Draw(255, 280);
            break;
        default:
            nextBlock.Draw(270, 270);
    }
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0) {
        gameOver = false;
        Reset();
    }
    
    switch (keyPressed) {
        case KEY_LEFT:
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
            MoveBlockRight();
            break;
        case KEY_DOWN:
            MoveBlockDown();
            UpdateScore(0, 1);
            break;
        case KEY_UP:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft() {
    if (!gameOver) {
        currBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false) {
            currBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight() {
    if (!gameOver) {
        currBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false) {
            currBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown() {
    if (!gameOver) {
        currBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false) {
            currBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.IsCellOutside(item.row, item.col)) {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock() {
    if (!gameOver) {
        currBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false) {
            currBlock.UndoRotate();
        }
    }
}

void Game::LockBlock() {
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles) {
        grid.grid[item.row][item.col] = currBlock.id;
    }
    PlaySound(stackSounds[rand() % stackSounds.size()]);

    currBlock = nextBlock;
    if (BlockFits() == false) {
        PlaySound(AUGH);
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0) {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currBlock.GetCellPositions();
    for (Position item : tiles) {
        if (grid.IsCellEmpty(item.row, item.col) == false) {
            return false;
        }
    }
    return true;
}

void Game::Reset() {
    grid.InitGrid();
    blocks = GetAllBlocks();
    currBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    switch (linesCleared) {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score =+ 500;
            break;
        default: 
            break;
    }
    score += moveDownPoints;
}
