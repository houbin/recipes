#############################################################   
# Makefile
# #############################################################  
# #set your own environment option  
CC = g++
CC_FLAG = -g -Wall -Wno-unused-parameter -Werror -fPIC -m32
#CC_FLAG = -Wall -Wno-unused-parameter -Werror -fPIC -m32 
#-march=i686
#   
#   #set your inc and lib
INC = -I./include -I./src/ -I./util
LIB = -lpthread -lrt -lstdc++ -lm -L./libs -lcJSON -lgrpc
  
#make target lib and relevant obj
PRG = watchdog

OBJ = src/watchdog.o src/watchdog_main.o util/clock.o util/coding.o util/cond.o util/crc32c.o util/logger.o \
util/mutex.o util/thread.o util/timer.o util/env_posix.o util/grpc_udp_service.o

C_OBJ = grpc/watchdog.o grpc/watchdog_s_userdef.o

all:$(PRG)

$(PRG):$(OBJ) $(C_OBJ)
	$(CC) -m32 -fPIC -o install/$(PRG) $(OBJ) $(C_OBJ) $(LIB)

.SUFFIXES: .c .o .cc
%.o : %.cc
	$(CC) $(CC_FLAG) $(INC) -c $*.cc -o $*.o

%.o : %.c
	$(CC) $(CC_FLAG) $(INC) -c $*.c -o $*.o


.PRONY:clean
clean:
	@echo "Removing linked and compiled files......;"
	-rm -f $(OBJ) install/$(PRG) $(C_OBJ)
