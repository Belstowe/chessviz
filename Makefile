C = gcc
compile_flag = -Wall -Werror -c
compile_debug_flag = -Wall -Werror -g -O0 -c
link_flag = -o
lib = -lm

all: Main.o
	$(C) ./build/*.o $(link_flag) ./bin/chessviz $(lib)

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/main.o

.PHONY: clean
clean:
	rm -rf ./build/*.*
