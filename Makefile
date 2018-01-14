CXXFLAGS=-std=c++11 -Wall -Wextra
OBJ=main.o List.o Long.o

all: main

main: $(OBJ)

clean:
	rm -f *.o main
