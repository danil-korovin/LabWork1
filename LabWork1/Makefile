CXX = g++
CXXFLAGS = -Wall -g -std=c++17

PROJECT = main
SOURCES = main.cpp binfunc.cpp
HEADERS = header.h
OBJ = $(SOURCES:.cpp=.o)

all: $(PROJECT)

$(PROJECT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(PROJECT)

.PHONY: all clean
