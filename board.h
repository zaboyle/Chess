#ifndef BOARD_H
#define BOARD_H

//#include "pieces.h"
//#include <vector>
//not sure about this one
#include <cassert>
#include "player.h"



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
	Board(Player* player1_in, Player* player2_in) {
		//initializer list gave me issues?
		//something about static/nonstatic data members
		player1 = player1_in;
		player2 = player2_in;
		//no need to do anything with array since it will be filled with junk values??
		nextPlayerToMove = nullptr;
		//create the pieces to start with

		//black pieces at top of board
		boardPieces[0][7] = new Rook("a8", "black");
		boardPieces[1][7] = new Knight("b8", "black");
		boardPieces[2][7] = new Bishop("c8", "black");
		boardPieces[3][7] = new Queen("d8", "black");
		boardPieces[4][7] = new King("e8", "black");
		boardPieces[5][7] = new Bishop("f8", "black");
		boardPieces[6][7] = new Knight("g8", "black");
		boardPieces[7][7] = new Rook("h8", "black");
		//row of pawns
		for (char c = 'a'; c < 'i'; ++c) {
			std::string loc = "";
			loc.append(std::to_string(c));
			loc.append("7");
			boardPieces[c - 97][6] = new Pawn(loc, "black");
		}

		//white pieces at bottom
		boardPieces[0][0] = new Rook("a1", "white");
		boardPieces[1][0] = new Knight("b1", "white");
		boardPieces[2][0] = new Bishop("c1", "white");
		boardPieces[3][0] = new Queen("d1", "white");
		boardPieces[4][0] = new King("e1", "white");
		boardPieces[5][0] = new Bishop("f1", "white");
		boardPieces[6][0] = new Knight("g1", "white");
		boardPieces[7][0] = new Rook("h1", "white");
		//row of pawns
		for (char c = 'a'; c < 'i'; ++c) {
			std::string loc = "";
			loc.append(std::to_string(c));
			loc.append("2");
			boardPieces[c - 97][1] = new Pawn(loc, "white");
		}
		//...

		/*NEED TO INITIALIZE THE OTHER SPOTS TO NULL POINTERS*/
		for (int row = 0; row < 8; ++row) {
			for (int col = 2; col < 6; ++col) {
				boardPieces[row][col] = nullptr;
			}
		}

		//push back all the board pieces to player1 and player2's vectors
		//depending on if they are black or white
		if (player1_in->getTeam() == "white") {
			//if player1 is white, give them the white pieces
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 2; ++j) {
					player1_in->addPiece(boardPieces[i][j]);
				}
			}
			//and give player2 black
			for (int i = 8; i > 6; --i) {
				for (int j = 0; j < 8; ++j) {
					player2_in->addPiece(boardPieces[j][i]);
				}
			}
			nextPlayerToMove = player1_in;
		}
		else {
			//otherwise, player 2 gets white
			for (int i = 0; i < 8; ++i) {
				for (int j = 0; j < 2; ++j) {
					player2_in->addPiece(boardPieces[i][j]);
				}
			}
			//and player1 gets black
			for (int i = 8; i > 6; --i) {
				for (int j = 0; j < 8; ++j) {
					player1_in->addPiece(boardPieces[j][i]);
				}
			}
			nextPlayerToMove = player2_in;
		}
	}
	//...

	//board copy ctor
	Board(Board* board_in) {
		this->player1 = board_in->player1;
		this->player2 = board_in->player2;
		this->nextPlayerToMove = board_in->nextPlayerToMove;

		for (int r = 0; r < 8; ++r) {
			for (int c = 0; c < 8; ++c) {
				Piece* piece = board_in->boardPieces[r][c];

				if (piece != nullptr) {
					std::string location = char(piece->getLocation().first) + std::to_string(piece->getLocation().second);

					if (piece->getAbbr() == "P") {
						this->boardPieces[r][c] = new Pawn(location, piece->getTeam());
					}
					else if (piece->getAbbr() == "N") {
						this->boardPieces[r][c] = new Knight(location, piece->getTeam());
					}
					else if (piece->getAbbr() == "B") {
						this->boardPieces[r][c] = new Bishop(location, piece->getTeam());
					}
					else if (piece->getAbbr() == "R") {
						this->boardPieces[r][c] = new Rook(location, piece->getTeam());
					}
					else if (piece->getAbbr() == "Q") {
						this->boardPieces[r][c] = new Queen(location, piece->getTeam());
					}
					else if (piece->getAbbr() == "K") {
						this->boardPieces[r][c] = new King(location, piece->getTeam());
					}
				}
				else {
					this->boardPieces[r][c] = nullptr;
				}

			}
		}
	}

	bool isPieceAtLoc(std::string destination) {
		if ((boardPieces[destination[0] - 97][destination[1] - 48]) != nullptr) { return true; }
		return false;
	}

	bool isPieceInTheWay(Piece* piece, std::string destination) {
		//needed for all pieces except knights
		//iterate between all x and y values that are hit

		//adjusting for ASCII '0'
		destination[1] -= 48;

		if (piece->getAbbr() == "P") {

		}
		else if (piece->getAbbr() == "B") {

		}
		else if (piece->getAbbr() == "R") {

		}
		else if (piece->getAbbr() == "Q") {

		}
		else if (piece->getAbbr() == "K") {
			//because the king can only move one space at a time
			return isPieceAtLoc(destination);
		}
		return false;
	}

	//board ctor with fen string? or csv file (would be easier)

	//returns true if the move for the given piece is in the bounds of the board
	bool inBounds(std::string destination) {
		//the first part of the location is a char, so subtract 97 because
		//that is the decimal value for 'a'
		//second part of the location must also be in range [0, 8)
		if (destination[0] - 97 >= 0 && destination[0] - 97 < 8 
			&& destination[1] - 48 >= 0 && destination[1] - 48 < 8) {
			return true;
		}
		return false;
	}

	//returns true if the user-inputted destination is a valid place for the piece to move
	//to and false otherwise. Includes taking pieces
	bool legalMove(Player* player, std::string piece_start_pos, std::string piece_destination) {

		Piece* piece = player->findByLocation(piece_start_pos);

		//if the piece is out of bounds or it's not a valid move, it is not legal
		if (!inBounds(piece_destination) || !(piece->validMove(piece_destination, piece->getTeam()))) { return false; }
		//this is mostly for pawns, since all other pieces take the same way they move
		if (isPieceAtLoc(piece_destination) && !piece->validTake(piece_destination, piece->getTeam())) { return false; }

		//if there is a piece in the way, it is not legal
		if (isPieceInTheWay(piece, piece_destination)) { return false; }

		//if the move results in the player being in check, it is not valid
		if (moveResultsInCheck(player, piece_start_pos, piece_destination)) { return false; }

		//if the piece can perform the move, return true
		return true;
	}

	//REQUIRES: the move is legal
	//moves the piece to the given destination
	//make sure to update the nextPlayerToMove pointer
	void movePiece(Player* player_in, std::string piece_start_pos, std::string piece_destination) {
		//this will cause an infinite loop because movePiece is called within legalMove
		//assert(this->legalMove(player_in, piece_start_pos, piece_destination));
		//
		Player* otherPlayer = nullptr;
		if (player_in == player1) { otherPlayer = player2; }
		else { otherPlayer = player1; }

		player_in->makeMove(piece_start_pos, piece_destination);

		//remove the piece from the player's pieces if it is being taken
		if (this->isPieceAtLoc(piece_destination)) {
			otherPlayer->removePiece(piece_destination);
			//also remove the piece from the board
			delete boardPieces[piece_destination[0] - 97][piece_destination[1] - 48];
			boardPieces[piece_destination[0] - 97][piece_destination[1] - 48] = nullptr;
		}
	}

	//returns true if the player is in check. false otherwise
	bool isInCheck(Player* player_in) {
		//need to find king destination here
		Piece* king = player_in->getKing();
		//need to do some fancy stuff here since the location is a pair
		std::pair<char, int> location = king->getLocation();
		std::string loc = location.first + std::to_string(location.second);
		//make sure it actually concatenated string, not just added ASCII values
		//assert(loc.length() == unsigned int(2));

		Player* otherPlayer = nullptr;
		if (player_in == player1) { otherPlayer = player2; }
		else { otherPlayer = player1; }

		for (auto iter = (otherPlayer->pieces).begin(); iter < (otherPlayer->pieces).end(); ++iter) {
			//if any opponent's piece can reach a player's king, they are in check
			if ((*iter)->validTake(loc, (*iter)->getTeam())) {
				return true;
			}
		}
		return false;
	}

	//returns true if the 
	bool moveResultsInCheck(Player* player, std::string piece_start_pos, std::string piece_destination) {
		Board testBoard(this);
		//now we have a board that is a copy of the current board
		//if we make this move on the test board, and the player is still in check,
		//we will know this move results in check

		testBoard.movePiece(player, piece_start_pos, piece_destination);
		if (testBoard.isInCheck(player)) { return true; }

		return false;
		//no need to worry about testBoard dtor because it is called implicitly when the function exits
	}


	//returns true if the questioned player has been checkmated
	bool isCheckmate(Player* player_in) {
		//basic logic:
		//
		//for every piece left, if even one can move s.t. the player is no longer in check, return false
		//to return true, all pieces must not be able to get the player out of check

		//!!!!loop through ALL moves for ALL pieces in here!!!!
		//this is costly
		for (Piece* piece : player_in->pieces) {
			
			//get the string form of the start location of the piece
			std::string piece_start = char(piece->getLocation().first) + std::to_string(piece->getLocation().second);

			for (char r = 'a'; r < 'i'; ++r) {
				for (int c = 0; c < 8; ++c) {
					//create string of the possible move location for each piece
					std::string possible_move_loc = r + std::to_string(c);
					//now the string should have values between [a-h][0-7]

					if (this->legalMove(player_in, piece_start, possible_move_loc)) { return false; }
				}
			}
		}
		return true;
	}

	//returns true if the player can castle with the king and the inputted rook. they must not be in check
	bool canCastle(Player* player_in, Piece* piece_in) {
		//cannot castle if in check
		if (this->isInCheck(player_in)) { return false; }

		//making sure the king hasn't moved
		std::pair<char, int> king_loc = player_in->getKing()->getLocation();
		if (player_in->getTeam() == "black" && king_loc != std::pair<char,int> {'e', 8}) { return false; }
		if (player_in->getTeam() == "white" && king_loc != std::pair<char, int> {'e', 1}) { return false; }
		
		//if we've gotten here, the king has not been moved. so we need to check that the rook hasn't either
		
		//starting positions are different for different teams
		
		//need to also make sure no pieces are in between!

		std::pair<char, int> rook_loc = piece_in->getLocation();

		if (piece_in->getAbbr() == "R") {
			if(player_in->getTeam() == "black" && 
				(king_loc == std::pair<char, int> {'a', 8} || king_loc == std::pair<char, int> {'h', 8})) {

				//making sure there are no pieces in between the rook and king!
				if (rook_loc.first > king_loc.first) {
					for (int i = king_loc.first; i < rook_loc.first; ++i) {
						//every piece in between must be nullptr
						if (boardPieces[i - 97][7] != nullptr) { return false; }
					}
					return true;
				}
				if (king_loc.first > rook_loc.first) {
					for (int i = rook_loc.first; i < king_loc.first; ++i) {
						//every piece in between must be nullptr
						if (boardPieces[i - 97][7] != nullptr) { return false; }
					}
					return true;
				}
			}
			if (player_in->getTeam() == "white" &&
				(king_loc == std::pair<char, int> {'a', 1} || king_loc == std::pair<char, int> {'h', 1})) {
				
				//making sure there are no pieces in between the rook and king!

				if (rook_loc.first > king_loc.first) {
					for (int i = king_loc.first; i < rook_loc.first; ++i) {
						//every piece in between must be nullptr
						if (boardPieces[i - 97][0] != nullptr) { return false; }
					}
					return true;
				}
				if (king_loc.first > rook_loc.first) {
					for (int i = rook_loc.first; i < king_loc.first; ++i) {
						//every piece in between must be nullptr
						if (boardPieces[i - 97][0] != nullptr) { return false; }
					}
					return true;
				}
			}
		}
		return false;
	}

	//performs a castle for the given pieces
	void castle(Piece* piece1, Piece* piece2) {
		
		//IMPLEMENT

	}

	std::string getBoardPiecesAbbrAt(int row, int col) const {
		return boardPieces[row][col]->getAbbr();
	}
	

	Player* getPlayer1() {
		return player1;
	}

	Player* getPlayer2() {
		return player2;
	}

	//destructor
	~Board() {
		for (int r = 0; r < 8; ++r) {
			for (int c = 0; c < 8; ++c) {
				if (boardPieces[r][c] != nullptr) { 
					delete boardPieces[r][c];
					boardPieces[r][c] = nullptr;
				}
			}
		}
		delete player1;
		player1 = nullptr;
		delete player2;
		player2 = nullptr;
		//DO NOT delete nextPlayerToMove because that would be a double free
	}

	private:
		//the board is a 2D array of pieces. array points to the pieces.
		//if no piece is there, the pointer is a nullptr
		Piece * boardPieces[8][8];
		Player* player1;
		Player* player2;
		Player* nextPlayerToMove;


};
#endif