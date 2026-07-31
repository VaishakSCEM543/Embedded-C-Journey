# Makefile for 04-Arrays module
# This file automates the compilation of all array examples.
# To use: just type 'make' in your terminal (if you have MinGW installed).

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Find all .c files in the current directory
SOURCES = $(wildcard *.c)
# Convert all .c filenames into .exe filenames (for Windows)
EXECUTABLES = $(SOURCES:.c=.exe)

# Default target: build everything
all: $(EXECUTABLES)

# Rule to compile any .c file into a .exe file
%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

# Target to clean up all executables
clean:
	del /Q *.exe 2>nul || rm -f *.exe

.PHONY: all clean
