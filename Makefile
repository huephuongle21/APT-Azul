.default: all

all: main

clean:
	rm -f main *.o

main: main.o GameManager.o StudentCredit.o LinkedList.o Vector.o Player.o Board.o Utility.o Tile.o SetupManager.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -g -c $^
