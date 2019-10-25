########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -std=c99
EJS = game_exe
########################################################
OBJECTS = game_loop.o game_reader.o game.o graphic_engine.o screen.o space.o command.o player.o object.o set.o die.o
########################################################
.PHONY: clean clear

all: $(EJS)

game_exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o game_exe $(OBJECTS)

game_reader.o: game_reader.c game_reader.h game.h command.h space.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

game_loop.o: game_loop.c graphic_engine.h game.h game_reader.h command.h space.h types.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h game_reader.h command.h space.h types.h object.o player.o die.h die.c
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c screen.h graphic_engine.h game.h command.h space.h types.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h set.c set.h types.h
	$(CC) $(CFLAGS) -c space.c

player.o: player.c player.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

#######################
# TESTS
#######################
# DIE
#############
die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o die_test $^

die_test.o: die_test.c die.c die.h
	$(CC) $(CFLAGS) -c die_test.c
#############

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
