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
constexpr int PATTERN_DIM = 16;
constexpr int PIXEL_SIZE = 10;
 
// Kich thuoc ban co (so hang / cot). Dung cho ca Table va cac vong lap ve/kiem tra thang.
constexpr int BOARD_SIZE = 3;
 
// Kich thuoc 1 o vuong tren man hinh, tinh bang pixel
constexpr int CELL_SIZE = 150;
 
// Toa do goc tren-trai cua ban co tren cua so game (pixel)
constexpr int OFFSET_X = 50;
constexpr int OFFSET_Y = 50;

// Chieu cao vung UI phia duoi ban co (dung de hien thi text ket qua + nut "Play Again")
constexpr int UI_PANEL_HEIGHT = 90;
 
// Kich thuoc cua so game: du de chua ban co + le xung quanh
constexpr int SCREEN_WIDTH  = OFFSET_X * 2 + CELL_SIZE * BOARD_SIZE;
constexpr int SCREEN_HEIGHT = OFFSET_Y * 2 + CELL_SIZE * BOARD_SIZE +  UI_PANEL_HEIGHT;

// Kich thuoc va vi tri nut "Play Again" (tu dong can giua theo chieu ngang man hinh)
constexpr int BUTTON_WIDTH  = 160;
constexpr int BUTTON_HEIGHT = 40;
constexpr int BUTTON_X = (SCREEN_WIDTH - BUTTON_WIDTH) / 2;
constexpr int BUTTON_Y = OFFSET_Y * 2 + CELL_SIZE * BOARD_SIZE + 40;
 
// Quy uoc gia tri luu trong Table cho tung nguoi choi (dung xuyen suot project)
constexpr int EMPTY_CELL   = 0;
constexpr int PLAYER_X     = 1;
constexpr int PLAYER_O     = 2;
//X-O pattern texture path
constexpr const char* TEXTURE_X_PATH = "../asset/patternX.png";
constexpr const char* TEXTURE_O_PATH = "../asset/patternO.png";
constexpr const char* TEXTURE_CELL_PATH = "../asset/cell.png";
} // namespace Config

 
#endif