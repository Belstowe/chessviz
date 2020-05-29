#ifndef BOARD_H
#define BOARD_H

short side_of_piece(char c);
char cell_column(int cell[2]);
char cell_row(int cell[2]);
unsigned check_move_col(const char move[], int cell[2]);
unsigned check_move_row(const char move[], int cell[2]);
int* cell_compose(const char cell_str[]);
char* piece_name_print(char c);
char* to_lower_case(char str[]);

#endif