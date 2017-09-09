CC = gcc

ineffablemake: ineffable.o ineffable_lexer.o
	$(CC) -c ineffablemake ineffable.o ineffable_lexer.o -I
