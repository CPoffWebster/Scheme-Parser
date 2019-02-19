
#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "schemer," which just takes a line of input and
#breaks it up into tokens.

scheme: lextester.o lexer.o
	gcc -o scheme lextester.o lexer.o

lextester.o: lextester.c
	gcc -c lextester.c

lexer.o: lexer.c
	gcc -c lexer.c

clean:
	rm -f *~ *.o *.a

#^^^^^^This space must be a TAB!!.

