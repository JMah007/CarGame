CC = gcc
CFLAGS  = -Wall -g -pedantic -ansi 
OBJ = main.o game.o misc.o
EXEC = traffic

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: main.c game.h misc.h boolean.h
	$(CC) $(CFLAGS) main.c -c

game.o: misc.c game.h boolean.h
	$(CC) $(CFLAGS) game.c -c

misc.o: misc.c
	$(CC) $(CFLAGS) misc.c -c

clean:
	rm $(EXEC) $(OBJ)