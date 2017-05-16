CXX = clang++
CXXFLAGS = --std=c++11 -g -Wall -Wextra

.PHONY: clean

PA1: PA1.o
	$(CXX) $(CXXFLAGS) $< -o $@

PA1.o : points.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean::
	rm PA1 PA1.o
