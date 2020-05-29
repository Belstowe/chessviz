#include <board.h>
#include <board_read.h>

#include <ctest.h>
#include <stdlib.h>

char* assign_string(const char str[])
{
    unsigned size = 1;
    for (; str[size] != '\0'; size++)
        ;

    char* result = malloc(size * sizeof(char));
    for (unsigned i = 0; i < size; i++)
        result[i] = str[i];

    return result;
}

CTEST(string_interprete, moves_division)
{
    char* move_white;
    char* move_black;
    int substrs;

    char* test_move1 = assign_string("1. e2-e4 e7-e5");
    substrs = move_string_split(&test_move1, &move_white, &move_black);
    ASSERT_EQUAL(111, substrs);
    ASSERT_STR("1.", test_move1);
    ASSERT_STR("e2-e4", move_white);
    ASSERT_STR("e7-e5", move_black);

    char* test_move2 = assign_string("e2-e4 e7-e5");
    substrs = move_string_split(&test_move2, &move_white, &move_black);
    ASSERT_EQUAL(11, substrs);
    ASSERT_STR("e2-e4", move_white);
    ASSERT_STR("e7-e5", move_black);
}

CTEST(string_interprete, piece_recognition)
{
    ASSERT_EQUAL('P', check_piece("e2-e4"));
    ASSERT_EQUAL('Q', check_piece("Qh5xf7#"));
}

CTEST(string_interprete, get_move)
{
    Cell *orig_cell, *goto_cell;
    char move_type;
    char move_situation;

    char* test_move1 = assign_string("e2-e4 e7-e5");
    orig_cell = cell_compose(test_move1);
    move_type = check_move_type(&test_move1);
    goto_cell = cell_compose(test_move1);
    move_situation = check_move_situation(test_move1);

    ASSERT_EQUAL('e', cell_column(orig_cell));
    ASSERT_EQUAL('2', cell_row(orig_cell));
    ASSERT_EQUAL('e', cell_column(goto_cell));
    ASSERT_EQUAL('4', cell_row(goto_cell));
    ASSERT_EQUAL('-', move_type);
    ASSERT_EQUAL('\0', move_situation);

    char* test_move2 = assign_string("Qh5xf7#");
    orig_cell = cell_compose(test_move2);
    move_type = check_move_type(&test_move2);
    goto_cell = cell_compose(test_move2);
    move_situation = check_move_situation(test_move2);

    ASSERT_EQUAL('h', cell_column(orig_cell));
    ASSERT_EQUAL('5', cell_row(orig_cell));
    ASSERT_EQUAL('f', cell_column(goto_cell));
    ASSERT_EQUAL('7', cell_row(goto_cell));
    ASSERT_EQUAL('x', move_type);
    ASSERT_EQUAL('#', move_situation);
}

CTEST(move_validity, valid_syntax_moves)
{
    char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

    ASSERT_EQUAL(0, check_white_move(board, "e2-e4"));
    ASSERT_EQUAL(0, check_black_move(board, "e7-e5"));
    ASSERT_EQUAL(0, check_white_move(board, "Bf1-c4"));
    ASSERT_EQUAL(0, check_black_move(board, "Nb8-c6"));
    ASSERT_EQUAL(0, check_white_move(board, "Qd1-h5"));
    ASSERT_EQUAL(0, check_black_move(board, "Ng8-f6"));
    ASSERT_EQUAL(1, check_white_move(board, "Qh5xf7#"));
}

CTEST(move_validity, invalid_syntax_moves)
{
    char board[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
                        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}};

    ASSERT_EQUAL(-1, check_white_move(board, "e2e4"));
    ASSERT_EQUAL(-1, check_white_move(board, "e4f"));
    ASSERT_EQUAL(-1, check_white_move(board, "1"));
    ASSERT_EQUAL(-1, check_white_move(board, "YOLO"));

    ASSERT_EQUAL(0, check_white_move(board, "Be2-e4"));
    ASSERT_EQUAL(0, check_white_move(board, "Be4xe5-ssss"));
}

CTEST(move_validity, pawn_valid_move)
{
    Cell *orig_cell, *goto_cell;

    orig_cell = cell_compose("e2");
    goto_cell = cell_compose("e4");
    ASSERT_EQUAL(Valid, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e4");
    goto_cell = cell_compose("e5");
    ASSERT_EQUAL(Valid, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("g2");
    goto_cell = cell_compose("h3");
    ASSERT_EQUAL(Valid, check_move_validity('P', 'x', orig_cell, goto_cell));

    orig_cell = cell_compose("e7");
    goto_cell = cell_compose("e5");
    ASSERT_EQUAL(Valid, check_move_validity('p', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e5");
    goto_cell = cell_compose("e4");
    ASSERT_EQUAL(Valid, check_move_validity('p', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e4");
    goto_cell = cell_compose("d3");
    ASSERT_EQUAL(Valid, check_move_validity('p', 'x', orig_cell, goto_cell));
}

CTEST(move_validity, pawn_invalid_move)
{
    Cell *orig_cell, *goto_cell;

    orig_cell = cell_compose("e2");
    goto_cell = cell_compose("e4");
    ASSERT_EQUAL(PawnChopWrong, check_move_validity('P', 'x', orig_cell, goto_cell));

    orig_cell = cell_compose("e2");
    goto_cell = cell_compose("e5");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e3");
    goto_cell = cell_compose("e5");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e2");
    goto_cell = cell_compose("e1");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e2");
    goto_cell = cell_compose("f3");
    ASSERT_EQUAL(PawnColumnSwitchNoChop, check_move_validity('P', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e7");
    goto_cell = cell_compose("e5");
    ASSERT_EQUAL(PawnChopWrong, check_move_validity('p', 'x', orig_cell, goto_cell));

    orig_cell = cell_compose("e7");
    goto_cell = cell_compose("e4");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('p', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e6");
    goto_cell = cell_compose("e4");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('p', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e6");
    goto_cell = cell_compose("e7");
    ASSERT_EQUAL(PawnRowSwitchError, check_move_validity('p', '-', orig_cell, goto_cell));

    orig_cell = cell_compose("e6");
    goto_cell = cell_compose("f5");
    ASSERT_EQUAL(PawnColumnSwitchNoChop, check_move_validity('p', '-', orig_cell, goto_cell));
}