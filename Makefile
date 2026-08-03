# ============================================================
# Root Makefile — Embedded C Journey
# Builds all modules with a single command.
#
# Usage:
#   make all      — build every module
#   make clean    — remove all build outputs
#   make 01       — build only module 01
#   make 02       — build only module 02
#   make 03       — build only module 03
#   make 04       — build only module 04
#   make 05       — build only module 05
# ============================================================

CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

# ── Module directories ───────────────────────────────────────
MOD01 = 01-Datatypes-and-Variables
MOD02 = 02-Pointers-and-Memory
MOD03 = 03-Functions
MOD04 = 04-Arrays
MOD05 = 05-Strings

# ── Single-file sources per module ──────────────────────────
SRC01 = $(wildcard $(MOD01)/*.c)
SRC02 = $(wildcard $(MOD02)/*.c)
SRC04 = $(wildcard $(MOD04)/*.c)
SRC05 = $(wildcard $(MOD05)/*.c)

# ── Multi-file sub-projects in 03-Functions ─────────────────
SRC03_SINGLE = $(MOD03)/function_add.c \
               $(MOD03)/function_return.c

SRC03_MATH    = $(MOD03)/math-project/main.c \
                $(MOD03)/math-project/math.c

SRC03_CAST    = $(MOD03)/typecast-exercise/main.c \
                $(MOD03)/typecast-exercise/math.c

SRC03_CAST2   = $(MOD03)/lecture-07-multifile-typecast-exercise/main.c \
                $(MOD03)/lecture-07-multifile-typecast-exercise/math.c

# ── Output binaries ──────────────────────────────────────────
BIN01 = $(SRC01:.c=.exe)
BIN02 = $(SRC02:.c=.exe)
BIN04 = $(SRC04:.c=.exe)
BIN05 = $(SRC05:.c=.exe)

BIN03_SINGLE  = $(MOD03)/function_add.exe \
                $(MOD03)/function_return.exe
BIN03_MATH    = $(MOD03)/math-project/math_project.exe
BIN03_CAST    = $(MOD03)/typecast-exercise/typecast.exe
BIN03_CAST2   = $(MOD03)/lecture-07-multifile-typecast-exercise/typecast2.exe

ALL_BINS = $(BIN01) $(BIN02) $(BIN03_SINGLE) $(BIN03_MATH) \
           $(BIN03_CAST) $(BIN03_CAST2) $(BIN04) $(BIN05)

# ── Default target ───────────────────────────────────────────
.PHONY: all clean 01 02 03 04 05

all: 01 02 03 04 05
	@echo ""
	@echo "========================================="
	@echo " All modules built successfully!"
	@echo "========================================="

# ── Per-module targets ───────────────────────────────────────
01: $(BIN01)
	@echo "[01] Datatypes & Variables — OK"

02: $(BIN02)
	@echo "[02] Pointers and Memory — OK"

03: $(BIN03_SINGLE) $(BIN03_MATH) $(BIN03_CAST) $(BIN03_CAST2)
	@echo "[03] Functions — OK"

04: $(BIN04)
	@echo "[04] Arrays — OK"

05: $(BIN05)
	@echo "[05] Strings — OK"

# ── Compile rules ────────────────────────────────────────────

# Single .c → .exe
%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

# Multi-file projects
$(MOD03)/math-project/math_project.exe: $(SRC03_MATH)
	$(CC) $(CFLAGS) $^ -o $@

$(MOD03)/typecast-exercise/typecast.exe: $(SRC03_CAST)
	$(CC) $(CFLAGS) $^ -o $@

$(MOD03)/lecture-07-multifile-typecast-exercise/typecast2.exe: $(SRC03_CAST2)
	$(CC) $(CFLAGS) $^ -o $@

# ── Clean ────────────────────────────────────────────────────
clean:
	@echo "Cleaning all build outputs..."
	-del /Q /S *.exe 2>nul || find . -name "*.exe" -delete
	@echo "Done."
