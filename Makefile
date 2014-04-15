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
	@gcc obj/matrix.o obj/pthread.o obj/main.o -lpthread -L include -o bin/pthread

single: main.o matrix.o
	@gcc -c src/single.c -L include -o obj/single.o
	@gcc obj/matrix.o obj/single.o obj/main.o -L include -o bin/single

create_tests: all
	@rm -rf tests;
	@python create_tests.py

execute_tests: create_tests
	@sh excecute_tests.sh

plotting_results: execute_tests
	@rm -rf results
	@python plotting.py
	@sh plotting.sh

clean:
	@rm -rf obj/* bin/*
