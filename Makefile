C = gcc
compile_flag = -Wall -Werror -std=gnu99 -c
compile_debug_flag = -Wall -Werror -std=gnu99 -g -O0 -c
link_flag = -o
lib = -lm
test_include_local_headers = -I ./thirdparty -I ./src

all: clean Main.o BoardPrintPlain.o BoardPrintHtml.o BoardRead.o Board.o
	$(C) ./build/src/*.o $(link_flag) ./bin/chessviz $(lib)

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/src/main.o

BoardPrintPlain.o:
	$(C) $(compile_flag) ./src/board_print_plain.c -o ./build/src/board_print_plain.o

BoardPrintHtml.o:
	$(C) $(compile_flag) ./src/board_print_html.c -o ./build/src/board_print_html.o

Board.o:
	$(C) $(compile_flag) ./src/board.c -o ./build/src/board.o

BoardRead.o:
	$(C) $(compile_flag) ./src/board_read.c -o ./build/src/board_read.o

.PHONY: test clean debug

debug: Main.od BoardPrintPlain.od BoardPrintHtml.od BoardRead.od Board.od
	$(C) ./build/src/*.o $(link_flag) ./bin/chessviz $(lib)

Main.od:
	$(C) $(compile_debug_flag) ./src/main.c -o ./build/src/main.o

BoardPrintPlain.od:
	$(C) $(compile_debug_flag) ./src/board_print_plain.c -o ./build/src/board_print_plain.o

BoardPrintHtml.od:
	$(C) $(compile_debug_flag) ./src/board_print_html.c -o ./build/src/board_print_html.o

Board.od:
	$(C) $(compile_debug_flag) ./src/board.c -o ./build/src/board.o

BoardRead.od:
	$(C) $(compile_debug_flag) ./src/board_read.c -o ./build/src/board_read.o

clean:
	rm -rf ./build/*.o ./build/src/*.o ./build/test/*.o

test: clean TMain.o BoardPrintPlain.o BoardPrintHtml.o BoardRead.o Board.o TBoard.o
	$(C) ./build/test/*.o ./build/src/*.o $(link_flag) ./bin/test

TMain.o:
	$(C) $(test_include_local_headers) $(compile_flag) ./test/main.c -o ./build/test/main.o

TBoard.o:
	$(C) $(test_include_local_headers) $(compile_flag) ./test/t_board.c -o ./build/test/t_board.o
