#include "functions.h"
#include "raylib.h"
 
// Ve toan bo bang len man hinh (vi du don gian, ban co the chinh lai theo y thich)
void drawTable(const Table& table) {
    int cellSize = 150;
    int offsetX = 50;
    int offsetY = 50;
 
    for (int r = 0; r < table.getRows(); r++) {
        for (int c = 0; c < table.getCols(); c++) {
            int x = offsetX + c * cellSize;
            int y = offsetY + r * cellSize;
            DrawRectangleLines(x, y, cellSize, cellSize, BLACK);
        }
    }
}
 
// Ve ky hieu X hoac O tai vi tri (row, col) dua theo gia tri trong Table
// Quy uoc: 1 = X, 2 = O, 0 = o trong
void drawXO(const Table& table, int row, int col) {
    int cellSize = 150;
    int offsetX = 50;
    int offsetY = 50;
 
    int value = table.getValue(row, col);
    int x = offsetX + col * cellSize;
    int y = offsetY + row * cellSize;
 
    if (value == 1) {
        // Ve chu X bang 2 duong cheo
        DrawLine(x + 20, y + 20, x + cellSize - 20, y + cellSize - 20, RED);
        DrawLine(x + cellSize - 20, y + 20, x + 20, y + cellSize - 20, RED);
    } else if (value == 2) {
        // Ve chu O bang duong tron
        DrawCircleLines(x + cellSize / 2, y + cellSize / 2, cellSize / 2 - 20, BLUE);
    }
}
 
// Xac dinh o (row, col) ma con tro chuot dang tro toi
bool getCellFromMouse(const Table& table, int mouseX, int mouseY,
                       int cellSize, int offsetX, int offsetY,
                       int& outRow, int& outCol)
{
    int relX = mouseX - offsetX;
    int relY = mouseY - offsetY;
 
    // Chuot nam ben trai/tren bang -> khong hop le
    if (relX < 0 || relY < 0) {
        return false;
    }
 
    int col = relX / cellSize;
    int row = relY / cellSize;
 
    // Chuot nam ngoai vung ban co
    if (row < 0 || row >= table.getRows() || col < 0 || col >= table.getCols()) {
        return false;
    }
 
    outRow = row;
    outCol = col;
    return true;
}
 
