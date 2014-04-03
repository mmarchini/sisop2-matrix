all: process pthread

main.o: matrix.o
	@gcc -c src/main.c -L include -o obj/main.o

matrix.o:
	@gcc -c src/matrix.c -L include -o obj/matrix.o

process: main.o matrix.o
	@gcc -c src/process.c -L include -o obj/process.o
	@gcc obj/matrix.o obj/process.o obj/main.o -L include -o bin/process

pthread: main.o matrix.o
	@gcc -c src/pthread.c -L include -o obj/pthread.o
	@gcc obj/matrix.o obj/pthread.o obj/main.o -L include -o bin/pthread

clean:
	@rm -rf obj/* bin/*
