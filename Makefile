#TODO:
#add dependencies here:

all: pieces_tests player_tests board_tests chess

pieces_tests: pieces_tests.cpp pieces.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 pieces_tests.cpp pieces.cpp -o pieces_tests

player_tests: player_tests.cpp player.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 player_tests.cpp player.cpp -o player_tests

board_tests: board_tests.cpp board.cpp
	g++ -Wall -Werror -pedantic -g --std=c++11 board_tests.cpp board.cpp -o board_tests

chess: main.cpp game.h board.h pieces.h player.h
	g++ -Wall -Werror -pedantic -g --std=c++11 main.cpp board.h player.h pieces.h -o chess

clean:
	rm -rvf main board_tests player_tests pieces_tests *~ *.out *.dSYM *.stackdump