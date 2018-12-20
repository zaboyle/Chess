#include "game.h"
/*
CHESS

Zach Boyle
zboyle@umich.edu
4/24/2018


////MAKE 'GAME' ADT////
generic game functionalities:
	- play against human or cpu (determined during the program)
	- load previous game
	- warns user when they're in check
	- user must get out of check if in it. aka they cannot make other moves
	- should support all legal chess moves. That is, 
		- castling
		- en passant
		- promotion
		- etc
	- game ends with checkmate OR user types "quit"
*/

int main() {
	Game game;
	game.play();
	return 0;
}