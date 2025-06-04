CXX = g++
CXXFLAGS = -Wall -g -std=c++17 -pthread

PROJECT = main
SOURCES = main.cpp binfunc.cpp
TESTS = test.cpp
HEADERS = header.h
OBJ = $(SOURCES:.cpp=.o)
TEST_OBJ = test.o binfunc.o
GTEST_LIB = -lgtest -lgtest_main -pthread

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

test.o: test.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROJECT) test test.o


.PHONY: all clean test
