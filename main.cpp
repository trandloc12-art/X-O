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
 
    // Vùng hình chữ nhật của nút "Play Again", dùng chung cho cả vẽ lẫn kiểm tra click
    Rectangle playAgainButton = {
        (float)Config::BUTTON_X,
        (float)Config::BUTTON_Y,
        (float)Config::BUTTON_WIDTH,
        (float)Config::BUTTON_HEIGHT
    };
 
    while (!WindowShouldClose()) {
        // ---------- 1. Update ----------
        Vector2 mousePos = GetMousePosition();
 
        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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
 
        // Chỉ cho bấm "Play Again" khi ván đấu đã kết thúc (thắng/thua/hòa)
        if (gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(mousePos, playAgainButton)) {
            // Tạo lại bàn cờ mới hoàn toàn trống, reset về trạng thái ban đầu
            board = Table(Config::BOARD_SIZE, Config::BOARD_SIZE);
            currentPlayer = Config::PLAYER_X;
            gameOver = false;
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
 
        if (gameOver) {
            // Hiển thị kết quả ván đấu
            if (isWinXO(board, Config::PLAYER_X)) {
                DrawText("Player X wins!", Config::OFFSET_X, Config::BUTTON_Y - 30, 20, RED);
            } else if (isWinXO(board, Config::PLAYER_O)) {
                DrawText("Player O wins!", Config::OFFSET_X, Config::BUTTON_Y - 30, 20, BLUE);
            } else if (isBoardFull(board)) {
                DrawText("It's a draw!", Config::OFFSET_X, Config::BUTTON_Y - 30, 20, GRAY);
            }
 
            // Đổi màu nút khi rê chuột vào (hover) để người chơi biết đây là nút bấm được
            bool hovering = CheckCollisionPointRec(mousePos, playAgainButton);
            DrawRectangleRec(playAgainButton, hovering ? SKYBLUE : LIGHTGRAY);
            DrawRectangleLinesEx(playAgainButton, 2, DARKGRAY);
            DrawText("Play Again",
                     (int)playAgainButton.x + 20,
                     (int)playAgainButton.y + 10,
                     20, BLACK);
        }
 
        EndDrawing();
    }
 
    CloseWindow();
    return 0;
}