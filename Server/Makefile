CXX = g++
CPPFLAGS = -Iinc -Isrc -Itest -I../common/inc
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

PRODUCT = main
TESTPRODUCT = test_$(PRODUCT)

.phony: all clean

all: $(PRODUCT)

$(PRODUCT): $(OBJECTS) ../common/libcommon.a
	$(CXX) -o $@ $(OBJECTS)  $(LIBS) ../common/libcommon.a

$(OBJECTS): $(HEADERS) Makefile 

$(TESTPRODUCT): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -f $(PRODUCT) $(OBJECTS) $(TESTPRODUCT) *.out

test: $(TESTPRODUCT)
	./$(TESTPRODUCT)
