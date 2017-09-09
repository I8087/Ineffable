CC = gcc

ineffable: ineffable.o ineffable_lexer.o
	$(CC) -c ineffable ineffable.o ineffable_lexer.o
