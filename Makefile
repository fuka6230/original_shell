shell: header.h main.o tokenize.o
	gcc main.o tokenize.o -o shell


tokenize.o: tokenize.c header.h
	gcc tokenize.c -c -o tokenize.o

main.o: main.c
	gcc main.c -c -o main.o