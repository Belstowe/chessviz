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

short sideOf(char c) {
  if ((signed short)'Z' - (signed short)c < 1) //if figure is black 
    return -1;
  else
    return 1;
}



char interprete(unsigned short c) {
  return c+'a';
}

char* figurepr(char c) {
  switch (c) {
    case 'r':
      return "Black Rook";
    case 'n':
      return "Black Knight";
    case 'b':
      return "Black Bishop";
    case 'q':
      return "Black Queen";
    case 'k':
      return "Black King";
    case 'p':
      return "Black Pawn";
    case 'R':
      return "White Rook";
    case 'N':
      return "White Knight";
    case 'B':
      return "White Bishop";
    case 'Q':
      return "White Queen";
    case 'K':
      return "White King";
    case 'P':
      return "White Pawn";
    default:
      return "Unknown";
  }
}

int main() {
  char cur, figure;
  // char *str_buf = malloc(MAX_STRING_SIZE * sizeof(char));
  // char *str_point = str_buf;
  unsigned short move = 1, readm = 1;
  short cell[2], behave, ifMate = 0;
  int ibuf1 = 0, ibuf2 = 0;

  char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                      {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                      {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                      {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

  printf("Welcome to Chessviz!\nThis program is used to interprete moves on chessboard.\n\nExample:\n1. e2-e4 e7-e5\n2. Bf1-c4 Nb8-c6\n3. Qd1-h5 Ng8-f6\n4. Qh5xf7#\n\nPress Ctrl+D to stop input and view chessboard.\n");

  while ((cur = getchar()) != EOF) {
    //putchar(cur);
    if (cur != '\n') {
      //*(str_point++) = cur;
      if (cur == ' ')
        continue;

      switch (readm) {
        case 1: //Num. of move
          if (cur >= '0' && cur <= '9') {
            ibuf2 *= (pow(10, ibuf1++));
			      ibuf2 += (cur - '0');
          } else if (cur == '.') {
            readm++;
            if (move != ibuf2) {
              printf(
                  " <!-- (ALERT: A number of move is misspecified. Expected '%d', "
                  "got "
                  "'%d'.) --> \n",
                  move, ibuf2);
            }
            move++;
          } else {
            printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
            return 0;
          }
          break;

        case 2:
          if ((cur >= 'a') && (cur <= 'h')) {
            figure = 'P';
            readm++;
          }
          else {
            if ((cur == 'K') || (cur == 'Q') || (cur == 'R') || (cur == 'B') || (cur == 'N'))
              figure = cur;
            else
              printf(" <!-- (ALERT: Unknown figure.) --> \n");
            readm++;
            break;
          }

          case 3:
            if ((cur >= 'a') && (cur <= 'h'))
              cell[0] = cur - 'a';
            else if ((cur >= 'A') && (cur <= 'H')) {
              cell[0] = cur - 'A';
              printf(" <!-- (ALERT: Move letter is in capital form.) --> \n");
            }
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 4:
            if ((cur >= '1') && (cur <= '8'))
              cell[1] = cur - '1';
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 5:
            if (board[cell[1]][cell[0]] == ' ') {
              printf(" <!-- (ERROR: No figure on %c%d.) --> \n", interprete(cell[0]), cell[1]);
              return 0;
            }
            else if (board[cell[1]][cell[0]] != figure) {
              printf(" <!-- (ALERT: Figure on %c%d is wrong. Expected %s, got %s.) --> \n", interprete(cell[0]), cell[1]+1, figurepr(figure), figurepr(board[cell[1]][cell[0]]));
            }
            readm++;

          case 6:
            switch (cur) {
              case '-':
                behave = 0;
                break;
              case 'x':
                behave = 1;
                break;
              default:
                printf(" <!-- (ERROR: Unknown type of move.) --> \n");
                return 0;
            }
            board[cell[1]][cell[0]] = ' ';
            readm++;
            break;

          case 7:
            if ((cur >= 'a') && (cur <= 'h'))
              cell[0] = cur - 'a';
            else if ((cur >= 'A') && (cur <= 'H')) {
              cell[0] = cur - 'A';
              printf(" <!-- (ALERT: Move letter is in capital form.) --> \n");
            }
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 8:
            if ((cur >= '1') && (cur <= '8'))
              cell[1] = cur - '1';
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 9:
            if (board[cell[1]][cell[0]] == ' ') {
              if (behave == 1)
                printf(" <!-- (ALERT: Capture was expected, but there is no piece.) --> \n");
            }
            else {
              if (behave == 0)
                printf(" <!-- (ALERT: Capture wasn't expected, but there is another piece.) --> \n");
              if ((figure-'Z'-1) * (board[cell[1]][cell[0]]-'Z'-1) > 0) { //If both pieces are of one side
                printf(" <!-- (ERROR: Piece is trying to capture its own ally on %c%d.) --> \n", interprete(cell[0]), cell[1]+1);
                return 0;
              }
            }
            board[cell[1]][cell[0]] = figure;
            readm++;

          case 10:
            if (cur == '+') {
              //isCheck = 1;
              readm++;
              break;
            }
            else if (cur == '#') {
              ifMate = 1;
              readm = 19;
              break;
            }
            readm++;

          case 11:
          if ((cur >= 'a') && (cur <= 'h')) {
            figure = 'p';
            readm++;
          }
          else {
            if ((cur == 'K') || (cur == 'Q') || (cur == 'R') || (cur == 'B') || (cur == 'N'))
              figure = cur - 'A' + 'a';
            else
              printf(" <!-- (ALERT: Unknown figure.) --> \n");
            readm++;
            break;
          }

          case 12:
            if ((cur >= 'a') && (cur <= 'h'))
              cell[0] = cur - 'a';
            else if ((cur >= 'A') && (cur <= 'H')) {
              cell[0] = cur - 'A';
              printf(" <!-- (ALERT: Move letter is in capital form.) --> \n");
            }
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 13:
            if ((cur >= '1') && (cur <= '8'))
              cell[1] = cur - '1';
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 14:
            if (board[cell[1]][cell[0]] == ' ') {
              printf(" <!-- (ERROR: No figure on %c%d.) --> \n", interprete(cell[0]), cell[1]);
              return 0;
            }
            else if (board[cell[1]][cell[0]] != figure) {
              printf(" <!-- (ALERT: Figure on %c%d is wrong. Expected %s, got %s.) --> \n", interprete(cell[0]), cell[1]+1, figurepr(figure), figurepr(board[cell[1]][cell[0]]));
            }
            readm++;

          case 15:
            switch (cur) {
              case '-':
                behave = 0;
                break;
              case 'x':
                behave = 1;
                break;
              default:
                printf(" <!-- (ERROR: Unknown type of move.) --> \n");
                return 0;
            }
            board[cell[1]][cell[0]] = ' ';
            readm++;
            break;

          case 16:
            if ((cur >= 'a') && (cur <= 'h'))
              cell[0] = cur - 'a';
            else if ((cur >= 'A') && (cur <= 'H')) {
              cell[0] = cur - 'A';
              printf(" <!-- (ALERT: Move letter is in capital form.) --> \n");
            }
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 17:
            if ((cur >= '1') && (cur <= '8'))
              cell[1] = cur - '1';
            else {
              printf(" <!-- (ERROR: Unknown symbol: '%c'.) --> \n", cur);
              return 0;
            }
            readm++;
            break;

          case 18:
            if (cur == '+') {
              //isCheck = 2;
              break;
            }
            else if (cur == '#') {
              ifMate = 2;
              readm = 19;
              break;
            }
         }
    } else if (readm == 18) {
      if (board[cell[1]][cell[0]] == ' ') {
        if (behave == 1)
          printf(" <!-- (ALERT: Capture was expected, but there is no piece.) --> \n");
        }
        else {
          if (behave == 0)
            printf(" <!-- (ALERT: Capture wasn't expected, but there is another piece.) --> \n");
          if ((figure-'Z'-1) * (board[cell[1]][cell[0]]-'Z'-1) > 0) { //If both pieces are of one side
            printf(" <!-- (ERROR: Piece is trying to capture its own ally on %c%d.) --> \n", interprete(cell[0]), cell[1]+1);
            return 0;
          }
        }
        board[cell[1]][cell[0]] = figure;
        ibuf1 = ibuf2 = ifMate = 0;
        readm = 1;
      }
      else if (readm < 18) {
        printf(" <!-- (ERROR: Not a full move. Exiting...) --> \n");
        return 0;
      }
      else {
        break;
      }
  }

  printf("\n\n");
  for (int i = 8; i > 0; i--) {
    printf("%d ", i);
    for (int j = 0; j < 8; j++) {
      printf("%c ",board[i-1][j]);
    }
    printf("\n");
  }
  printf("  ");
  for (int i = 0; i < 8; i++)
    printf("%c ",i+'a');
  printf("\n");
  if (ifMate == 1)
    printf("Checkmate to black!");
  else if (ifMate == 2)
    printf("Checkmate to white!");
  printf("\n");
}
