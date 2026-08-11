# Makefile for 07-Bitwise-Operators module

CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

SOURCES     = $(wildcard *.c)
EXECUTABLES = $(SOURCES:.c=.exe)

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	del /Q *.exe 2>nul || rm -f *.exe

.PHONY: all clean
