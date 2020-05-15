#ifndef BOARD_H
#define BOARD_H

short side_of_piece(char c);
char cell_column(int cell[2]);
char cell_row(int cell[2]);
char* piece_name_print(char c);

#endif