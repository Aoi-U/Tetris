#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid() {
    nRows = 20;
    nCols = 10;
    cellSize = 30;
    InitGrid();
    colors = GetCellColors();
}

void Grid::InitGrid() {
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print() {
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw() {
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            int cellValue = grid[row][col];
            DrawRectangle(col * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int col) {
    if (row >= 0 && row < nRows && col >= 0 && col < nCols)
        return false;
    return true;
}

bool Grid::IsCellEmpty(int row, int col) {
    if (grid[row][col] == 0) {
        return true;
    }
    return false;
}

int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = nRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) {
    for (int col = 0; col < nCols; col++) {
        if (grid[row][col] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int col = 0; col < nCols; col++) {
        grid[row][col] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int col = 0; col < nCols; col++) {
        grid[row + numRows][col] = grid[row][col];
        grid[row][col] = 0;
    }
}
