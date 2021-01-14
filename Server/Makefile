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

PRODUCT = main
TESTPRODUCT = test_$(PRODUCT)

.phony: $(PRODUCT) clean $(TESTPRODUCT)

all: $(PRODUCT) obj

$(PRODUCT): $(SOURCES) $(HEADERS) Makefile
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LIBS)

obj: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS)

$(TESTPRODUCT): $(TEST_SOURCES) $(TEST_HEADERS) Makefile
	@$(CXX) $(CXXFLAGS) $(TEST_SOURCES) -o $@ $(TEST_LIBS)

clean:
	@rm -f $(PRODUCT) $(OBJECTS) $(TESTPRODUCT) *.out

test: $(TESTPRODUCT)
	@./$(TESTPRODUCT)
