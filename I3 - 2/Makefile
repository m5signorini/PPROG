########################
# MAKEFILE
# author: Martin Sanchez Signorini
# version: 2.0
# TO-DO: Automatic tests generation
########################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -std=c99 -I$(IDIR)
# Flags for making the dependency files
DFLAGS= -MT $@ -MMD -MP -MF $(patsubst $(ODIR)/%.o,$(DDIR)/%.d,$@)

DDIR = deps
CDIR = src
IDIR = include
ODIR = obj

# Using [patsubst pattern, replacement, text] - Change text
# Using [wildcard pattern] - Get text
######################################
TESTS = die_test set_test inventory_test link_test
SRC_FILES = $(wildcard $(CDIR)/*.c)
TST_O = $(patsubst %,$(ODIR)/%.o,$(TESTS))
SRC_O = $(patsubst $(CDIR)/%.c,$(ODIR)/%.o,$(SRC_FILES))
OBJ_FILES = $(SRC_O) $(TST_O)

all: game_exe $(TESTS)

# LINK GAME - Dont use *_test.o, multiple mains
game_exe: $(filter-out $(TST_O),$(SRC_O))
	$(CC) $(CFLAGS) -o $@ $^
die_test: $(ODIR)/die_test.o $(ODIR)/die.o
	$(CC) $(CFLAGS) -o $@ $^
set_test: $(ODIR)/set_test.o $(ODIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^
link_test: $(ODIR)/link_test.o $(ODIR)/link.o
	$(CC) $(CFLAGS) -o $@ $^
inventory_test: $(ODIR)/inventory_test.o $(ODIR)/inventory.o $(ODIR)/set.o
	$(CC) $(CFLAGS) -o $@ $^

#$(TESTS): %_test : $(ODIR)/%_test.o $(ODIR)/%.o
#	$(CC) $(CFLAGS) -o $@ $^

# CREATE OBJS
$(ODIR)/%.o: $(CDIR)/%.c
$(ODIR)/%.o: $(CDIR)/%.c $(DDIR)/%.d | $(DDIR)
	$(CC) $(DFLAGS) $(CFLAGS) -c -o $@ $<
# Prerequisites are the .c and .d files, exclude deps in case its missing
# Create deps if its missing
$(DDIR): ; @mkdir -p $@

# Variable with the corresponding .d files for every .c file
DEP_FILES := $(SRC_FILES:$(CDIR)/%.c=$(DDIR)/%.d)

# Include all the .d files in to the makefile
$(DEP_FILES):
include $(wildcard $(DEP_FILES))

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o

clear:
	rm -rf game_exe $(TESTS)

run:
	@echo ">>>>>>Running the GAME"
	./game_exe data.dat -l game_log.log

runv:
	@echo ">>>>>>Running the GAME"
	valgrind --leak-check=full ./game_exe data.dat

runv_new:
	@echo ">>>>>>Running the GAME"
	valgrind --leak-check=full ./game_exe data.dat < partida_nueva_oca -l game_log.log

runv_old:
	@echo ">>>>>>Running the GAME"
	valgrind --leak-check=full ./game_exe data.dat < partida_vieja_oca -l game_log.log
