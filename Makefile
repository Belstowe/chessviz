C = gcc
compile_flag = -Wall -Werror -c
compile_debug_flag = -Wall -Werror -g -O0 -c
link_flag = -o

all: foldermake Main.o
	cp ./src/*.c ./build/
	$(C) $(link_flag) ./build/*.c -o ./bin/chessviz

Main.o:
	$(C) $(compile_flag) ./src/main.c -o ./build/main.o

foldermake:
	mkdir -p bin
	mkdir -p build

.PHONY: clean
clean:
	rm -rf ./build/*
