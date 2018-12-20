#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "pieces.h"

using std::vector;

class Board {

	/*
	- standard board is:
	- black on top, white on bottom
  +----+----+----+----+----+----+----+----+
8 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
7 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
6 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
5 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
4 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
3 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
2 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
1 |    |    |    |    |    |    |    |    |
  +----+----+----+----+----+----+----+----+
0 (This row is only used to allow for 1-indexing.
   aka, to index the board for the Game ADT, you use the actual 
   character and row. ex: board[a][1] gives BL corner)
  +----+----+----+----+----+----+----+----+
    a    b    c    d    e    f    g    h
	*/

//make everything pubilc so that the Game class can do its job easily
private:
	vector<vector<Piece*>> board;

public:
	//default ctor
	Board() {
		//initialize board
		board.resize(8);
		for(auto &vec : board) {
			vec.resize(9);
		}
		//initialize all black pieces
		board[0][8] = new Rook(Team::black);
		board[1][8] = new Knight(Team::black);
		board[2][8] = new Bishop(Team::black);
		board[3][8] = new Queen(Team::black);
		board[4][8] = new King(Team::black);
		board[5][8] = new Bishop(Team::black);
		board[6][8] = new Knight(Team::black);
		board[7][8] = new Rook(Team::black);
		//black pawns
		for(int i = 0; i < 8; ++i) {
			board[i][7] = new Pawn(Team::black);
		}

		//initialze all white pieces
		board[0][1] = new Rook(Team::white);
		board[1][1] = new Knight(Team::white);
		board[2][1] = new Bishop(Team::white);
		board[3][1] = new Queen(Team::white);
		board[4][1] = new King(Team::white);
		board[5][1] = new Bishop(Team::white);
		board[6][1] = new Knight(Team::white);
		board[7][1] = new Rook(Team::white);
		//white pawns
		for(int i = 0; i < 8; ++i) {
			board[i][2] = new Pawn(Team::white);
		}

		//fill the rest with nullptrs in case they arent already
		for(int i = 0; i < 8; ++i) {
			board[i][3] = nullptr;
			board[i][4] = nullptr;
			board[i][5] = nullptr;
			board[i][6] = nullptr;
		}
	}

	//overload the [] operator to allow the Game class
	//to easily get info from the board
	vector<Piece*> &operator[](char row) {
		return board[row - 'a'];
	}

	~Board() {
		//delete all Piece pointers
		//takes advantage of how nothing happens when you delete nullptr
		for(auto &row : board) {
			for(Piece* p : row) {
				delete p;
			}
		}
	}

};
#endif //BOARD_H