#define MAX_STRING_SIZE 256
#include <stdio.h>

int pow(int num, int power) {
  int buf = num;
  if (power == 0) {
    return 1;
  }
  for (; power > 1; power--) {
    num *= buf;
  }
  return num;
}

Boolean r_expect(char sym, char c_min, char c_max) {
  if (sym >= c_min && sym <= c_max) {
    return true;
  } else {
    printf("ERROR. Incorrect syntaxis. Expected '%c'..'%c', recieved '%c'.\n",
           c_min, c_max, sym);
    return false;
  }
}

int main() {
  char cur;
  char *str_buf = malloc(MAX_STRING_SIZE * sizeof(char)), str_point = str_buf;
  unsigned short move = 1;
  int ibuf1 = 0, ibuf2 = 0;
  char board[8][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};

  while (((cur = getchar()) != '\n') && (cur != EOF)) {
    *(str_point++) = cur;
    putchar(cur);
  }
}