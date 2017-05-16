CXX = clang++
CXXFLAGS = --std=c++11 -g -Wall -Wextra

.PHONY: clean

PA2: PA2.o
	$(CXX) $(CXXFLAGS) $< -o $@

PA2.o : MSCT.cpp Ds.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean::
	rm PA2 PA2.o
