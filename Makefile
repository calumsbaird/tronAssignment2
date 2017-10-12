CC=gcc
CFLAGS=-g -Wall -std=c99 -Iinclude
LIBS=
TARGET=calc
TESTTARGET=test

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
TEST_DIR = testing
_DEPS = calc.h

OBJECTFILES = calc.o checkInput.o simplifyInput.o
_OBJS = main.o $(OBJECTFILES)
TEST = testing/testing.c

DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))
OBJS = $(patsubst %,$(OBJ_DIR)/%,$(_OBJS))
TESTOBJS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECTFILES))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) 

$(TESTTARGET): $(TESTOBJS)
	$(CC) -o $@ $(TEST) $(TESTOBJS) $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(OBJS) $(TESTOBJS) $(TARGET) $(TESTTARGET)
