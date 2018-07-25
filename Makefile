all: pieces_tests

pieces_tests: pieces_tests.cpp pieces.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 pieces_tests.cpp pieces.cpp -o pieces_tests

player_tests: player_tests.cpp player.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 player_tests.cpp player.cpp -o player_tests

board_tests: board_tests.cpp board.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 board_tests.cpp board.cpp -o board_tests

main: main.cpp board.cpp player.cpp pieces.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 main.cpp board.cpp player.cpp pieces.cpp -o main

clean:
	rm -rvf main board_tests player_tests pieces_tests *~ *.out *.dSYM *.stackdump