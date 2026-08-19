#include "functions.h"
#include "raylib.h"
#include "../gameConfig.h"
 
// Ve toan bo bang len man hinh (vi du don gian, ban co the chinh lai theo y thich)
void drawTable(const Table& table) {
    static Texture2D texCell = LoadTexture(Config::TEXTURE_CELL_PATH);
    static bool filterApplied = []() {
        SetTextureFilter(texCell, TEXTURE_FILTER_POINT);
        return true;
    }();

    int cellSize = Config::CELL_SIZE;
    int offsetX = Config::OFFSET_X;
    int offsetY = Config::OFFSET_Y;
    int rows = table.getRows();
    int cols = table.getCols();

    
    Rectangle source = { 0, 0, (float)texCell.width, (float)texCell.height };// Rectangle nguồn: lấy toàn bộ ảnh gốc

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int cellX = offsetX + c * cellSize;
            int cellY = offsetY + r * cellSize;

            Rectangle dest = { (float)cellX, (float)cellY, (float)cellSize, (float)cellSize };
            Vector2 origin = { 0, 0 };   // điểm neo, không xoay nên để (0,0)

            DrawTexturePro(texCell, source, dest, origin, 0.0f, WHITE);
        }
    }
 
    
}
 
// Ve ky hieu X hoac O tai vi tri (row, col) dua theo gia tri trong Table
// Quy uoc: 1 = X, 2 = O, 0 = o trong
void drawXO(const Table& table, int row, int col) {
    // static: chỉ chạy khởi tạo này ĐÚNG 1 LẦN duy nhất, dù drawXO được gọi rất nhiều lần
    static Texture2D texX = LoadTexture(Config::TEXTURE_X_PATH);
    static Texture2D texO = LoadTexture(Config::TEXTURE_O_PATH);
    static bool filterApplied = []() {
        SetTextureFilter(texX, TEXTURE_FILTER_POINT);
        SetTextureFilter(texO, TEXTURE_FILTER_POINT);
        return true;
    }();

    int cellSize = Config::CELL_SIZE;
    int offsetX = Config::OFFSET_X;
    int offsetY = Config::OFFSET_Y;

    int value = table.getValue(row, col);
    if (value != Config::PLAYER_X && value != Config::PLAYER_O) return;

    Texture2D tex = (value == Config::PLAYER_X) ? texX : texO;

    // Hình sẽ chiếm 70% kích thước ô, chừa 30% làm khoảng trống (15% mỗi bên)
    float fillRatio = 0.7f;
    float targetSize = cellSize * fillRatio;

    int cellX = offsetX + col * cellSize;
    int cellY = offsetY + row * cellSize;

    // Rectangle nguồn: lấy toàn bộ ảnh gốc
    Rectangle source = { 0, 0, (float)tex.width, (float)tex.height };

    // Rectangle đích: vị trí + kích thước hiển thị, canh giữa trong ô
    Rectangle dest = {
        cellX + (cellSize - targetSize) / 2,
        cellY + (cellSize - targetSize) / 2,
        targetSize,
        targetSize
    };

    Vector2 origin = { 0, 0 };   // điểm neo, không xoay nên để (0,0)

    DrawTexturePro(tex, source, dest, origin, 0.0f, WHITE);
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
 
// Kiem tra nguoi choi 'player' da thang hay chua
// Dieu kien thang (luat caro): co it nhat Config::WIN_CONDITION quan LIEN TIEP
// theo 1 trong 4 huong: ngang, doc, cheo chinh, cheo phu.
// (Voi ban co dien 3x3, WIN_CONDITION = 3 se cho ket qua tuong duong luat cu.)
bool isWinXO(const Table& table, int player) {
    int rows = table.getRows();
    int cols = table.getCols();
    const int WIN = Config::WIN_CONDITION;
 
    // 4 huong kiem tra: (dr, dc)
    // (0,1)=ngang | (1,0)=doc | (1,1)=cheo chinh | (1,-1)=cheo phu
    const int dirs[4][2] = { {0, 1}, {1, 0}, {1, 1}, {1, -1} };
 
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (table.getValue(r, c) != player) continue;
 
            for (int d = 0; d < 4; d++) {
                int dr = dirs[d][0];
                int dc = dirs[d][1];
 
                // Chi bat dau dem tu O DAU TIEN cua 1 chuoi: kiem tra o lien truoc
                // (theo huong nguoc lai) co phai cung la 'player' khong.
                // Neu co -> o hien tai khong phai diem bat dau, bo qua de tranh dem trung
                // (vd chuoi XXXXX se bi dem lai 5 lan neu khong co buoc nay).
                int pr = r - dr, pc = c - dc;
                bool prevIsSame = (pr >= 0 && pr < rows && pc >= 0 && pc < cols &&
                                    table.getValue(pr, pc) == player);
                if (prevIsSame) continue;
 
                // Dem so quan lien tiep tu (r, c) di theo huong (dr, dc)
                int count = 1;
                int nr = r + dr, nc = c + dc;
                while (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                       table.getValue(nr, nc) == player) {
                    count++;
                    if (count >= WIN) return true; // du so quan lien tiep -> thang
                    nr += dr;
                    nc += dc;
                }
            }
        }
    }
 
    return false;
}
 
// Kiem tra ban co da day het chua (khong con o nao = 0)
// Dung ket hop voi isWinXO de xac dinh HOA:
// neu board day (isBoardFull == true) ma khong ai thang (isWinXO false ca 2 nguoi)
// => tran dau hoa
bool isBoardFull(const Table& table) {
    for (int r = 0; r < table.getRows(); r++) {
        for (int c = 0; c < table.getCols(); c++) {
            if (table.getValue(r, c) == Config::EMPTY_CELL) {
                return false; // van con o trong -> ban co chua day
            }
        }
    }
    return true; // khong con o trong nao
}