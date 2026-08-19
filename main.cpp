#include "raylib.h"
#include "dto/table.h"
#include "function/functions.h"

int main() {
    InitWindow(600, 600, "X-O Game");
    SetTargetFPS(60);

    // Table tạo NGOÀI vòng lặp — chỉ tạo 1 lần duy nhất, giữ trạng thái xuyên suốt
    Table board(3, 3);

    int cellSize = 200;   // 600 / 3 ô
    int offsetX = 0;
    int offsetY = 0;

    int currentPlayer = 1;   // 1 = X, 2 = O (khớp kiểu int trong Table)
    bool gameOver = false;

    while (!WindowShouldClose()) {
        // ---------- 1. Update ----------
        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePos = GetMousePosition();
            int row, col;

            bool valid = getCellFromMouse(board, (int)mousePos.x, (int)mousePos.y,
                                           cellSize, offsetX, offsetY, row, col);

            if (valid && board.getValue(row, col) == 0) {
                board.setValue(row, col, currentPlayer);

                // TODO: gọi hàm kiểm tra thắng ở đây khi bạn viết xong isWinXO
                // if (isWinXO(board, currentPlayer)) gameOver = true;
                if (isWinXO(board, currentPlayer)) {
                    gameOver = true;
                } else if (isBoardFull(board)) {
                    gameOver = true; // Hòa
                } 

                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }

        // ---------- 2. Draw ----------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawTable(board);

        // Duyệt toàn bộ ô, chỉ vẽ X/O ở ô nào đã có giá trị
        for (int r = 0; r < board.getRows(); r++) {
            for (int c = 0; c < board.getCols(); c++) {
                if (board.getValue(r, c) != 0) {
                    drawXO(board, r, c);
                }
            }
        }

        if (gameOver) {
            DrawText("Game Over", 200, 250, 30, RED);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}