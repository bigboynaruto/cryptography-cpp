all: main

main:
	g++ -std=c++11 -Wall -Wextra  *.cpp

clean:
	rm -f *.o main
