## Makefile for TextToHTML
## 27/04/22 Hu Yihui

MAKEFLAGS += -L 

CXX      = clang++
CXXFLAGS = -O2 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -O2 

TextToHTML: main.o
	$(CXX) $(LDFLAGS) -o gerp main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp