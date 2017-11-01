.PHONY: clean all
CC = g++
CPPFLAGS = -Wall -g -pthread -std=c++11
BIN = main 
SOURCES = $(BIN.=.cpp)

all: $(BIN)
$(BIN): $(SOURCES) thread_pool.cpp condition.cpp

clean:
	-rm -rf $(BIN) bin/ obj/ core
