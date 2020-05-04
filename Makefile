.default: all

all: main

clean:
	rm -f main *.o

main: main.o GameADT.o StudentCredit.o LinkedList.o Player.o Board.o Utility.o Tile.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -g -c $^