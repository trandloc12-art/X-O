#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "raylib.h"

void drawTable(const Table& table); // Function to draw the table on the console
void drawXO(const Table& table, int row, int col); // Function to draw the X and O symbols on the console based on the table data
bool isDrawXO(const Table& table, int row, int col); // Function to check if blank space is available for drawing X or O at the specified row and column
bool isWinXO(const Table& table, char player); // Function to check if the specified player has won the game based on the current state of the table
#endif // FUNCTIONS_H