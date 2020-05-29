#ifndef BOARD_READ_H
#define BOARD_READ_H

int read_string(char str_in[], unsigned limit);
int move_string_split(char* num[], char* move_white[], char* move_black[]);
char check_piece(char move[]);
char check_move_type(char* move[]);
char check_move_situation(char move[]);
int check_move_validity(
        char piece, int type, int orig_cell[2], int goto_cell[2]);
int check_white_move(char board[8][8], char move[]);
int check_black_move(char board[8][8], char move[]);
int check_num(char num[]);

#endif