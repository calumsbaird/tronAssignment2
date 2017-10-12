CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=
TARGET=calc
TESTTARGET=test

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
_DEPS = calc.h
_OBJS = calc.o main.o
TEST = testing/testing.c src/calc.c

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) 

$(TESTTARGET): testing/testing.o
	$(CC) -o $@ $(TEST) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJS) testing/testing.o $(TARGET) $(TESTTARGET)
