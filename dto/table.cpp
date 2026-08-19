#include "table.h"
#include <stdexcept>

// Constructor: khởi tạo rows, cols và tạo data kích thước r x c, toàn giá trị 0
Table::Table(int r, int c) : rows(r), cols(c), data(r, std::vector<int>(c, 0)) {}

// Gán giá trị vào ô [r][c], có kiểm tra bounds
void Table::setValue(int r, int c, int value) {
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        throw std::out_of_range("Index out of range");
    }
    data[r][c] = value;
}

// Lấy giá trị tại ô [r][c], có kiểm tra bounds
int Table::getValue(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        throw std::out_of_range("Index out of range");
    }
    return data[r][c];
}

// Lấy số hàng
int Table::getRows() const {
    return rows;
}

// Lấy số cột
int Table::getCols() const {
    return cols;
}

// Lấy toàn bộ dữ liệu bảng, trả về tham chiếu const để tránh copy và tránh bị sửa từ bên ngoài
const std::vector<std::vector<int>>& Table::getTable() const {
    return data;
}