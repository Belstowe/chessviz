#define MAX_STRING_SIZE 256
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
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
*/

/*
Boolean r_expect(char sym, char c_min, char c_max) {
  if (sym >= c_min && sym <= c_max) {
    return true;
  } else {
    printf("ERROR. Incorrect syntaxis. Expected '%c'..'%c', recieved '%c'.\n",
           c_min, c_max, sym);
    return false;
  }
}
*/

int main() {
  char cur;
  // char *str_buf = malloc(MAX_STRING_SIZE * sizeof(char));
  // char *str_point = str_buf;
  unsigned short move = 1, readm = 1;
  int ibuf1 = 0, ibuf2 = 0;
  /*
  char board[8][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
                      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                      {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
  */
  while ((cur = getchar()) != EOF) {
    putchar(cur);
    if (cur != '\n') {
      //*(str_point++) = cur;
      switch (readm) {
        case 1:
          if (cur >= '0' && cur <= '9') {
            ibuf2 += (cur - '0') * (pow(10, ibuf1++));
          } else if (cur == '.') {
            readm++;
            if (move != ibuf2) {
              printf(
                  " (ALERT: A number of move is misspecified. Expected '%d', "
                  "got "
                  "'%d'.) ",
                  move, ibuf2);
            }
            move++;
          } else {
            printf(" (ERROR: Unknown symbol: '%c'.) ", cur);
            break;
          }
      }
    } else {
      ibuf1 = ibuf2 = 0;
      readm = 1;
    }
  }
}