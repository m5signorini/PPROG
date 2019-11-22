########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -std=c99
EJS = game_exe set_test die_test
########################################################
OBJECTS = game_loop.o game_reader.o game.o graphic_engine.o screen.o space.o command.o player.o object.o set.o die.o link.o inventory.o
########################################################
.PHONY: clean clear

all: $(EJS)

game_exe: $(OBJECTS)
	$(CC) $(CFLAGS) -o game_exe $(OBJECTS)

game_reader.o: game_reader.c game_reader.h game.h command.h object.h player.h space.h die.h set.h inventory.h link.h types.h
	$(CC) $(CFLAGS) -c game_reader.c

game_loop.o: game_loop.c graphic_engine.h game.h game_reader.h command.h object.h player.h space.h die.h set.h inventory.h link.h types.h
	$(CC) $(CFLAGS) -c game_loop.c

game.o: game.c game.h game_reader.h command.h space.h die.h object.h player.h set.h link.h inventory.h types.h
	$(CC) $(CFLAGS) -c game.c

graphic_engine.o: graphic_engine.c screen.h graphic_engine.h game.h command.h space.h object.h player.h die.h inventory.h link.h set.h types.h
	$(CC) $(CFLAGS) -c graphic_engine.c

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) -c screen.c

space.o: space.c space.h set.h types.h
	$(CC) $(CFLAGS) -c space.c

player.o: player.c player.h inventory.h types.h
	$(CC) $(CFLAGS) -c player.c

object.o: object.c object.h types.h
	$(CC) $(CFLAGS) -c object.c

command.o: command.c command.h
	$(CC) $(CFLAGS) -c command.c

die.o: die.c die.h types.h
	$(CC) $(CFLAGS) -c die.c

set.o: set.c set.h types.h
	$(CC) $(CFLAGS) -c set.c

inventory.o: inventory.c inventory.h set.h types.h
		$(CC) $(CFLAGS) -c inventory.c

link.o: link.c link.h types.h
			$(CC) $(CFLAGS) -c link.c
#######################
# TESTS
#######################
# DIE
#############
die_test: die_test.o die.o
	$(CC) $(CFLAGS) -o die_test $^

die_test.o: die_test.c die.h
	$(CC) $(CFLAGS) -c die_test.c
	
# DIE
#############
inventory_test: inventory_test.o inventory.o set.o
	$(CC) $(CFLAGS) -o inventory_test $^

inventory_test.o: inventory_test.c types.h inventory.h
	$(CC) $(CFLAGS) -c inventory_test.c
#######################
# SET
#############
set_test: set_test.o set.o
	$(CC) $(CFLAGS) -o set_test $^

set_test.o: set_test.c set.h
	$(CC) $(CFLAGS) -c set_test.c
#######################

clear:
	rm -rf *.o

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running the GAME"
	./game_exe data.dat -l game_log.log

runv:
	@echo ">>>>>>Running the GAME"
	valgrind --leak-check=full ./game_exe data.dat -l game_log.log
