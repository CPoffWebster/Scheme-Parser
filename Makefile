# Charlie Poff-Webster

# This is the Makefile for main.c, parser.c and parser.h
# To use it, put it in the same directory as those three files.
# To compile, simply type "make" at the command line.
# To remove all object code, type "make clean" (this removes
# all ".o" and ".a" files)

# Executable file "scheme" depends on main.o and parser.o
scheme: main.o parser.o lexer.o
	gcc -o exec main.o parser.o lexer.o

main.o: main.c
	gcc -c main.c

parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

clean:
	rm -f *~ *.o *.a
#^^^This space must be a TAB!!.

