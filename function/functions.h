#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 
#include "../dto/table.h"
#include "raylib.h"
 
void drawTable(const Table& table); // Function to draw the table on the console/screen
void drawXO(const Table& table, int row, int col); // Function to draw the X and O symbols based on the table data
 
// Xac dinh o (row, col) ma con tro chuot dang tro toi dua tren toa do pixel (mouseX, mouseY).
// cellSize   : kich thuoc 1 o vuong (pixel)
// offsetX/Y  : toa do goc tren-trai cua bang tren man hinh
// outRow/Col : ket qua tra ve neu chuot nam trong bang
// Tra ve true neu toa do chuot nam trong bang, false neu nam ngoai.
bool getCellFromMouse(const Table& table, int mouseX, int mouseY,
                       int cellSize, int offsetX, int offsetY,
                       int& outRow, int& outCol);
 
#endif
 

