CXX=g++
CXX_FLAGS=-g
LIBS=-lpthread

MAKE_DIR=.
BIN_DIR=$(MAKE_DIR)/bin
SRC_DIR=$(MAKE_DIR)/src
OBJ_DIR=$(MAKE_DIR)/obj

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.cc
	$(CXX) $(CXX_FLAGS) -c $^ -o $@

all: $(BIN_DIR)/udp_client

$(BIN_DIR)/udp_client :$(OBJ_DIR)/main.o $(OBJ_DIR)/cond.o $(OBJ_DIR)/mutex.o $(OBJ_DIR)/config.o $(OBJ_DIR)/env_posix.o $(OBJ_DIR)/logger.o \
		$(OBJ_DIR)/thread.o $(OBJ_DIR)/udp_service.o $(OBJ_DIR)/clock.o
	$(CXX) $(CXX_FLAGS) -o $@ $(LIBS) $^

bak:

clean:
	rm $(OBJ_DIR)/*
	rm $(BIN_DIR)/*

