#include "raylib.h"
#include "dto/table.h"
#include "function/functions.h"
#include "GameConfig.h"
 
int main() {
    InitWindow(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, "X-O Game");
    SetTargetFPS(60);
 
    // Table tạo NGOÀI vòng lặp — chỉ tạo 1 lần duy nhất, giữ trạng thái xuyên suốt
    Table board(Config::BOARD_SIZE, Config::BOARD_SIZE);
 
    int currentPlayer = Config::PLAYER_X;   // 1 = X, 2 = O (khớp kiểu int trong Table)
    bool gameOver = false;
 
    while (!WindowShouldClose()) {
        // ---------- 1. Update ----------
        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int row, col;
 
            bool valid = getCellFromMouse(board, (int)mousePos.x, (int)mousePos.y,
                                           Config::CELL_SIZE, Config::OFFSET_X, Config::OFFSET_Y,
                                           row, col);
 
            if (valid && board.getValue(row, col) == Config::EMPTY_CELL) {
                board.setValue(row, col, currentPlayer);
 
                if (isWinXO(board, currentPlayer)) {
                    gameOver = true;
                } else if (isBoardFull(board)) {
                    gameOver = true; // Hòa
                }
 
                currentPlayer = (currentPlayer == Config::PLAYER_X) ? Config::PLAYER_O : Config::PLAYER_X;
            }
        }
 
        // ---------- 2. Draw ----------
        BeginDrawing();
        ClearBackground(RAYWHITE);
 
        drawTable(board);
 
        // Duyệt toàn bộ ô, chỉ vẽ X/O ở ô nào đã có giá trị
        for (int r = 0; r < board.getRows(); r++) {
            for (int c = 0; c < board.getCols(); c++) {
                if (board.getValue(r, c) != Config::EMPTY_CELL) {
                    drawXO(board, r, c);
                }
            }
        }
 
        if (isWinXO(board, Config::PLAYER_X)) {
            DrawText("Player X wins!", 150, Config::SCREEN_HEIGHT - 50, 20, RED);
        } else if (isWinXO(board, Config::PLAYER_O)) {
            DrawText("Player O wins!", 150, Config::SCREEN_HEIGHT - 50, 20, BLUE);
        } else if (isBoardFull(board)) {
            DrawText("It's a draw!", 150, Config::SCREEN_HEIGHT - 50, 20, GRAY);
        }
 
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}