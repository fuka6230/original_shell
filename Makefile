shell: header.h main.o tokenize.o parser.o
	gcc main.o tokenize.o parser.o -o shell