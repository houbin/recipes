OPT ?= -O2 -DNDEBUG 	# produce use
# OPT ?= -g2			# debug mode

CXX=g++
CC=gcc

CFLAGS += -I. -I./include $(OPT)
CXXFLAGS += -I. -I./include $(OPT)

LIBS=-lpthread -lleveldb

MAKE_DIR=.
BIN_DIR=$(MAKE_DIR)/bin
SRC_DIR=$(MAKE_DIR)/src
OBJ_DIR=$(MAKE_DIR)/obj

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $^ -o $@

all: $(BIN_DIR)/leveldb_tool

$(BIN_DIR)/leveldb_tool:$(OBJ_DIR)/leveldb_tool.o
	$(CXX) $(CXXFLAGS) -o $@ $(LIBS) $^ 

bak:

clean:
	rm $(OBJ_DIR)/*
	rm $(BIN_DIR)/*
