#ifndef BOARD_H
#define BOARD_H

typedef struct cell_t {
    int column;
    int row;
} Cell;

short side_of_piece(char c);
char cell_column(Cell* cell);
char cell_row(Cell* cell);
unsigned check_move_col(const char move[], Cell* cell);
unsigned check_move_row(const char move[], Cell* cell);
Cell* cell_compose(const char cell_str[]);
char* cell_decompose(const Cell* cell);
unsigned absolute(int num);
char* piece_name_print(char c);
char* to_lower_case(char str[]);

#endif