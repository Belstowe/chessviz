#include <board.h>

#include <ctest.h>

CTEST(board_assist, piece_side)
{
    const char white_piece = 'K';
    const char black_piece = 'b';
    const char unknown = '?';

    const int white_side_result = side_of_piece(white_piece);
    const int black_side_result = side_of_piece(black_piece);
    const int unknown_result = side_of_piece(unknown);

    ASSERT_EQUAL(white_side_result, 1);
    ASSERT_EQUAL(black_side_result, -1);
    ASSERT_EQUAL(unknown_result, 0);
}

CTEST(board_assist, cell_correct_name)
{
    // We will take g2 for example
    int cell[2];
    cell[0] = 6; // g
    cell[1] = 1; // 2

    const char cell_column_result = cell_column(cell);
    const char cell_row_result = cell_row(cell);

    ASSERT_EQUAL(cell_column_result, 'g');
    ASSERT_EQUAL(cell_row_result, '2');
}

CTEST(board_assist, pieces_names)
{
    char* piece_name;

    piece_name = piece_name_print('K');
    ASSERT_STR("White King", piece_name);

    piece_name = piece_name_print('b');
    ASSERT_STR("Black Bishop", piece_name);

    piece_name = piece_name_print('P');
    ASSERT_STR("White Pawn", piece_name);

    piece_name = piece_name_print(' ');
    ASSERT_STR("None", piece_name);

    piece_name = piece_name_print('l');
    ASSERT_STR("Unknown", piece_name);
}

CTEST(board_assist, lower_case_transform)
{
    ASSERT_STR("black king", to_lower_case("BLACK KING"));
    ASSERT_STR("white king", to_lower_case("white king"));
    ASSERT_STR("ladder", to_lower_case("LaDdEr"));
    ASSERT_STR(" ;", to_lower_case(" ;"));
}