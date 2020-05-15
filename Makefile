C = gcc
compile_flag = -Wall -Werror -std=c99 -c
compile_debug_flag = -Wall -Werror -std=c99 -g -O0 -c
link_flag = -o
lib = -lm

all: Main.o BoardPrintPlain.o
	$(C) ./build/*.o $(link_flag) ./bin/chessviz $(lib)

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/main.o

BoardPrintPlain.o:
	$(C) $(compile_flag) ./src/board_print_plain.c -o ./build/board_print_plain.o

.PHONY: clean
clean:
	rm -rf ./build/*.*
