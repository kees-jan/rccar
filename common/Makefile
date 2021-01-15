CXX = g++
CPPFLAGS = -Iinc -Isrc -Itest
CXXFLAGS = -Wall -Werror -Wextra -pedantic -ggdb -O0 $(CPPFLAGS) -std=c++11

LIBS = -lpthread
TEST_LIBS = -lgtest $(LIBS)

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard inc/*.h)

TEST_SOURCES = $(filter-out src/main.cpp, $(SOURCES)) \
			 $(wildcard test/*.cpp)
TEST_HEADERS = $(HEADERS) \
			   $(wildcard test/*.h)

OBJECTS=$(SOURCES:.cpp=.o)

PRODUCT = libcommon.a

.phony: all clean

all: $(PRODUCT)

$(PRODUCT): $(OBJECTS)
	ar rcs $@ $^

$(OBJECTS): $(HEADERS) Makefile 

clean:
	@rm -f $(PRODUCT) $(OBJECTS) $(TESTPRODUCT) *.out

test: $(TESTPRODUCT)
	./$(TESTPRODUCT)
