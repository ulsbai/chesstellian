CC      = g++
CXXFLAGS = -std=c++11 -g
OUTPUT   = chesstellian

SRCS     := $(wildcard *.cpp)
OBJS     := $(patsubst %.cpp,%.o,$(SRCS))
#SOURCES  := structs.h structs.cpp pieces.cpp moves.cpp test_legal_moves_func.cpp format.cpp

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

%.o : %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OUTPUT) $(OBJS)

.PHONY: all clean
