C = gcc
compile_flag = -Wall -Werror -c
compile_debug_flag = -Wall -Werror -g -O0 -c
link_flag = -o
lib = -lm

all: foldermake Main.o
	$(C) ./build/*.c $(link_flag) ./bin/chessviz $(lib)

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/main.o

foldermake:
	mkdir -p bin
	mkdir -p build

.PHONY: clean
clean:
	rm -rf ./build/*
