CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 -Isrc -Iinc -Wno-unused-variable -Iinclude/
SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard inc/*.h)
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = main

.PHONY: all clean

all: $(TARGET) $(OBJECTS)

$(TARGET): $(SOURCES) $(HEADERS) Makefile
	@$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

clean:
	@rm -f $(TARGET) $(OBJECTS)