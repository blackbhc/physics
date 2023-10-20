.PHONY: all clean test

TARGET = ""
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic -fsanitize=undefined -fsanitize=leak -O3 -Og

all: $(TARGET)
	@echo "Done"

test: test/test.cpp
	$(CXX) $(CXXFLAGS) -o test/test_demo test/test.cpp
	@test/test_demo
	@rm test/test_demo
