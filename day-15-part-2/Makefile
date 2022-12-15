
# define the C++ compiler to use
CC = g++

# define any compile-time flags
CFLAGS = -Wall -g -O3 -std=c++2a

all: main

main: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main


run: main
	./main < input.txt

clean:
	$(RM) main