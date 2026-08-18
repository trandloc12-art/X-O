#ifndef TABLE_H
#define TABLE_H

class Table {
private:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;
public:
    Table(int r, int c) : rows(r), cols(c);

    void setValue(int r, int c, int value);// Method to set a value in the table at specified row and column

    int getValue(int r, int c) const;// Method to get a value from the table at specified row and column

    int getRows() const;// Method to get the number of rows in the table
    int getCols() const;// Method to get the number of columns in the table
    const std::vector<std::vector<int>>& getTable() const;// Method to get the entire table data
};

