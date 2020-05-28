#ifndef BOARD_READ_H
#define BOARD_READ_H

int read_string(char str_in[], unsigned limit);
int move_string_split(char* num[], char* move_white[], char* move_black[]);
int check_white_move(char board[8][8], char move[]);
int check_black_move(char board[8][8], char move[]);
int check_num(char num[]);

#endif