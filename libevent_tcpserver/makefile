CC = g++
CFLAGS = -g
LIBS = -lpthread -levent

SERVER = tcp_server
CLIENT = test_client

all:$(SERVER) $(CLIENT)

$(SERVER):src/master.cc src/worker.cc src/main.cc src/connection.cc util/clock.cc util/coding.cc util/common.cc util/cond.cc \
	util/config.cc util/crc32c.cc util/logger.cc util/mutex.cc util/thread.cc util/timer.cc util/env_posix.cc
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(CLIENT):test/client_print.cc src/connection.cc util/coding.cc
	${CC} $(CFLAGS) -o $@ $^

clean:
	rm -f $(SERVER) $(CLIENT) *.o


