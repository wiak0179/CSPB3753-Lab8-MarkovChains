###############################################################################
# CSPB 3753 — Lab 8: Markov Chains
# Build rules for the Lab 8 executable (lab8).
#
# Author: Cole Akers
# Date: November, 5, 2025.
#
# Overview:
#   - Compiles main.c, matrix.c, and markov.c into the lab8 binary.
#   - Uses the same warning and standard flags as previous labs.
#
# Usage:
#   make        # build lab8
#   make clean  # remove object files and binary
#
###############################################################################

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -O2 -std=c11
TARGET  = lab8
OBJS    = main.o matrix.o markov.o

.PHONY: all clean

# Default target: build the executable.
all: $(TARGET)

# Link step: combine all object files into the final binary.
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile main.c into main.o. Depends on the headers it includes.
main.o: main.c matrix.h markov.h
	$(CC) $(CFLAGS) -c main.c

# Compile matrix.c into matrix.o. Depends on matrix.h.
matrix.o: matrix.c matrix.h
	$(CC) $(CFLAGS) -c matrix.c

# Compile markov.c into markov.o. Depends on markov.h and matrix.h.
markov.o: markov.c markov.h matrix.h
	$(CC) $(CFLAGS) -c markov.c

# Clean target: remove binary and object files.
clean:
	rm -f $(OBJS) $(TARGET)
