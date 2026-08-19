#ifndef GAMECONFIG_H
#define GAMECONFIG_H
 
// File nay chua cac gia tri DUNG CHUNG cho toan bo project (khong thuoc rieng
// mot class/module nao), giup tranh viec moi noi tu khai bao rieng mot bo
// cellSize/offsetX/offsetY -> de bi lech gia tri giua cac ham (vi du drawTable
// dung offsetX = 50 nhung getCellFromMouse lai truyen offsetX = 60...).
//
// Moi noi trong code (drawTable, drawXO, getCellFromMouse, main.cpp, ...)
// chi can #include "GameConfig.h" va dung thang cac hang so ben duoi,
// khong tu dinh nghia lai gia tri rieng nua.
 
namespace Config {
 
// Kich thuoc ban co (so hang / cot). Dung cho ca Table va cac vong lap ve/kiem tra thang.
constexpr int BOARD_SIZE = 3;
 
// Kich thuoc 1 o vuong tren man hinh, tinh bang pixel
constexpr int CELL_SIZE = 150;
 
// Toa do goc tren-trai cua ban co tren cua so game (pixel)
constexpr int OFFSET_X = 50;
constexpr int OFFSET_Y = 50;
 
// Kich thuoc cua so game: du de chua ban co + le xung quanh
constexpr int SCREEN_WIDTH  = OFFSET_X * 2 + CELL_SIZE * BOARD_SIZE;
constexpr int SCREEN_HEIGHT = OFFSET_Y * 2 + CELL_SIZE * BOARD_SIZE;
 
// Quy uoc gia tri luu trong Table cho tung nguoi choi (dung xuyen suot project)
constexpr int EMPTY_CELL   = 0;
constexpr int PLAYER_X     = 1;
constexpr int PLAYER_O     = 2;

const int patternX[16][16] = {
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
    {0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0},
    {0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0},
    {0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0},
    {0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1}
};

const int patternO[16][16] = {
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0}
};
} // namespace Config
 
#endif