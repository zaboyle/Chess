#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include <vector>
//not sure about this one
#include "player.h"
#include <cassert>

/*
////MAKE 'BOARD' ADT////
- standard board is:
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
    a    b    c    d    e    f    g    h

	examples:
	a1 = boardPieces[0][0]
	b1 = boardPieces[1][0]
	e3 = boardPieces[4][2]

- bottom right square is white
- checkered pattern
- white on bottom, black on top
- kings in the 'e' col

Functionality:
- should be printed after each move
- should ask user for move input with the standard positioning shown above
- after move is inputted, update board and switch turns
- reject an invalid move (print message and ask for valid input. That is,
	i. off the board
	ii. a piece is not allowed to move in that fashion

****work out issues with player****
Implementation ideas:
- need either friend class player or needs to own 2 players
as member variables to be able to print the board and such
- board has 2D array as member variable
- need a generic print function for black and white (since the board flips)


- each square either has a piece (represented as letters) or ""(if it's blank)
each square's piece also needs to have a "team" associated with it
^^^maybe^^^
*/


class Board {
public:

	//board ctor
	Board(Player* player1_in, Player* player2_in) : player1(player1_in), player2(player2_in) {
		//create the pieces to start with

		//black pieces at top of board
		boardPieces[0][8] = new Rook("a8");
		boardPieces[1][8] = new Knight("b8");
		boardPieces[2][8] = new Bishop("c8");
		boardPieces[3][8] = new Queen("d8");
		boardPieces[4][8] = new King("e8");
		boardPieces[5][8] = new Bishop("f8");
		boardPieces[6][8] = new Knight("g8");
		boardPieces[7][8] = new Rook("h8");
		//row of pawns
		for (int i = 0; i < 8; ++i) {
			boardPieces[i][7] = new Pawn((i + 97) + "7");
		}

		//white pieces at bottom
		boardPieces[0][0] = new Rook("a1");
		boardPieces[1][0] = new Knight("b1");
		boardPieces[2][0] = new Bishop("c1");
		boardPieces[3][0] = new Queen("d1");
		boardPieces[4][0] = new King("e1");
		boardPieces[5][0] = new Bishop("f1");
		boardPieces[6][0] = new Knight("g1");
		boardPieces[7][0] = new Rook("h1");
		//row of pawns
		for (int i = 0; i < 8; ++i) {
			boardPieces[i][2] = new Pawn((i + 97) + "2");
		}
		//...

		//push back all the board pieces to player1 and player2's vectors
		//depending on is they are black or white
		if (player1_in->getTeam() == "white") {
			//if player1 is white, give them the white pieces
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 8; ++j) {
					player1_in->addPiece(boardPieces[i][j]);
				}
			}
			//and give player2 black
			for (int i = 8; i > 6; --i) {
				for (int j = 0; j < 8; ++j) {
					player2_in->addPiece(boardPieces[i][j]);
				}
			}
			
		}
		else {
			//otherwise, player 2 gets white
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 8; ++j) {
					player2_in->addPiece(boardPieces[i][j]);
				}
			}
			//and player1 gets black
			for (int i = 8; i > 6; --i) {
				for (int j = 0; j < 8; ++j) {
					player1_in->addPiece(boardPieces[i][j]);
				}
			}
		}
		
		
		//...


	}

	//board ctor with fen string? or csv file (would be easier)

	//returns true if the move for the given piece is in the bounds of the board
	bool inBounds(std::string destination) {
		//the first part of the location is a char, so subtract 97 because
		//that is the decimal value for 'a'
		//second part of the location must also be in range [0, 8)
		if (destination[0] - 97 >= 0 && destination[0] - 97 < 8 
			&& destination[1] >= 0 && destination[1] < 8) {
			return true;
		}
		return false;
	}

	bool validTake(Piece* piece, std::string destination) {
		//returns true if the piece in question can take an opponent's piece at destination
	}

	//returns true if the user-inputted destination is a valid place for the piece to move
	//to and false otherwise. Includes taking pieces
	bool legalMove(Piece* piece, std::string destination) { 
		if (!inBounds(destination) || !(piece->validMove(destination))) { return false; }
		//if the piece can perform the move, return true
		return true;
	}

	//moves the piece to the given destination
	//make sure to update the nextPlayerToMove pointer
	void movePiece(Player* player, Piece* piece, std::string destination) {
		assert(legalMove(piece, destination));
		//
		player->makeMove(piece, destination);
	}

	//returns true if the player is in check. false otherwise
	bool isInCheck(Player* player_in) { return false; }

	//returns true if the questioned player has been checkmated
	bool isCheckmate(Player* player_in) { return false; }

	//returns true if the player can castle with the two pieces. they must not be in check
	bool canCastle(Piece* piece1, Piece* piece2, bool isInCheck) { return false; }

	//performs a castle for the given pieces
	void castle(Piece* piece1, Piece* piece2) {}

	std::string getBoardPiecesAbbrAt(int row, int col) const {
		return boardPieces[row][col]->getAbbr();
	}

private:
	//the board is a 2D array of pieces. array points to the pieces.
	//if no piece is there, the pointer is a nullptr
	Piece* boardPieces[8][8];
	Player* player1;
	Player* player2;
	Player* nextPlayerToMove;
};

//prints the board to the console in the given format
//with pieces represented as their symbols
std::ostream & operator<<(std::ostream &os, const Board &board) {
	//print board to os
	for (int row = 0; row < 8; ++row) {
		os << " +----+----+----+----+----+----+----+----+" << std::endl << (8 - row) << " ";
		for (int col = 0; col < 8; ++col) {
			os << "| " << board.getBoardPiecesAbbrAt(row, col) << " ";
		}
		os << "|" << std::endl;
	}
	os << " +----+----+----+----+----+----+----+----+" << std::endl;
	os << "   a    b    c    d    e    f    g    h" << std::endl << std::endl;
	return os;
}


#endif //