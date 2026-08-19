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
 //============================================================================================
 
// Kiem tra nguoi choi 'player' da thang hay chua
// Dieu kien thang: co it nhat 1 hang, 1 cot, hoac 1 duong cheo
// ma tat ca cac o deu bang 'player' (1 = X, 2 = O)
bool isWinXO(const Table& table, int player) {
    int n = table.getRows(); // gia su ban co vuong (rows == cols)
 
    // 1. Kiem tra tung HANG
    for (int r = 0; r < n; r++) {
        bool win = true;
        for (int c = 0; c < table.getCols(); c++) {
            if (table.getValue(r, c) != player) {
                win = false;
                break; // chi can 1 o sai la loai hang nay ngay, khoi kiem tra tiep
            }
        }
        if (win) return true; // ca hang nay toan player -> thang
    }
 
    // 2. Kiem tra tung COT
    for (int c = 0; c < table.getCols(); c++) {
        bool win = true;
        for (int r = 0; r < n; r++) {
            if (table.getValue(r, c) != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
 
    // 3. Kiem tra duong CHEO CHINH (tren-trai -> duoi-phai): (0,0),(1,1),(2,2)...
    {
        bool win = true;
        for (int i = 0; i < n; i++) {
            if (table.getValue(i, i) != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
 
    // 4. Kiem tra duong CHEO PHU (tren-phai -> duoi-trai): (0,n-1),(1,n-2),...
    {
        bool win = true;
        for (int i = 0; i < n; i++) {
            if (table.getValue(i, n - 1 - i) != player) {
                win = false;
                break;
            }
        }
        if (win) return true;
    }
 
    // Khong co hang/cot/cheo nao toan player -> chua thang
    return false;
}
 
// Kiem tra ban co da day het chua (khong con o nao = 0)
// Dung ket hop voi isWinXO de xac dinh HOA:
// neu board day (isBoardFull == true) ma khong ai thang (isWinXO false ca 2 nguoi)
// => tran dau hoa
bool isBoardFull(const Table& table) {
    for (int r = 0; r < table.getRows(); r++) {
        for (int c = 0; c < table.getCols(); c++) {
            if (table.getValue(r, c) == 0) {
                return false; // van con o trong -> ban co chua day
            }
        }
    }
    return true; // khong con o trong nao
}