CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=
TARGET=calc

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
_DEPS = calc.h
_OBJS = calc.o main.o

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TARGET)
