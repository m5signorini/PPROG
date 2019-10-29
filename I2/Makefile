########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -std=c99
EJS = game_exe
########################################################
OBJECTS = game_loop.o game_reader.o game.o graphic_engine.o screen.o space.o command.o player.o object.o
########################################################
.PHONY: clean clear

all: $(EJS)

game_exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o game_exe $(OBJECTS)

game_reader.o: game_reader.c game_reader.h game.h command.h space.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

game_loop.o: game_loop.c graphic_engine.h game.h game_reader.h command.h space.h types.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h game_reader.h command.h space.h types.h object.o player.o
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c screen.h graphic_engine.h game.h command.h space.h types.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h types.h
	$(CC) $(CFLAGS) -c space.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c


clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running the GAME"
	./game_exe data.dat

runv:
	@echo ">>>>>>Running the GAME"
	valgrind --leak-check=full ./game_exe data.dat
