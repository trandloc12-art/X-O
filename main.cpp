#include "raylib.h"

int main() {
    InitWindow(600, 600, "X-O Game");
    SetTargetFPS(60);
    
    // TODO: khai báo board[3][3], currentPlayer, gameState...
    
    while (!WindowShouldClose()) {
        // 1. Update: xử lý input, cập nhật board
        
        // 2. Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // vẽ lưới, X, O, text...
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}