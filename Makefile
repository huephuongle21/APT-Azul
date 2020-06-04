.default: all

all: main

clean:
	rm -f main *.o

main: main.o GameManager.o StudentCredit.o LinkedList.o Vector.o Player.o AbstractBoard.o Utility.o SetupManager.o Table.o 
ScoreCalculator.o AiManager.o AiTurn.o GreyBoard.o RegularBoard.o Advanced6TileBoard.o CurrentGameState.o Heuristic.o
	g++ -Wall -Werror -std=c++14 -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -O -g -c $^
