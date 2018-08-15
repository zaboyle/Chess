#ifndef PLAYER_H
#define PLAYER_H
#include "pieces.h"
//#include <string>
#include <vector>
/*
////MAKE 'PLAYER' ADT////
****work out issues with board****
//Implementation ideas:
- name as member variable
- "pieces" vector member variable that contains all pieces and their corresponding locations
if a piece is taken, it is removed from this vector
- each player has a "pieces taken" vector to keep track of
which of the opponent's pieces they've taken (optional)
- cpu has some sort of strat based on pieces' point values
- polymorphic for human or cpu
*/
class Player {

	friend class Board;

public:

	//MAY NOT NEED THIS//
	virtual Piece* find(Piece* piece) = 0;

	Piece* getKing() {
		for (auto iter = pieces.begin(); iter < pieces.end(); ++iter) {
			if ((*iter)->getAbbr() == "K") { return *iter; }
		}
	}

	virtual void makeMove(Piece* piece, std::string destination) = 0;

	virtual void addPiece(Piece* piece_in) {
		pieces.push_back(piece_in);
	}

	virtual void removePiece(Piece* piece) = 0;

	virtual ~Player() {}

	virtual void setTeam(std::string team_in) {
		team = team_in;
	}

	virtual std::string getTeam() {
		return team;
	}

	virtual void setName(std::string name_in) {
		name = name_in;
	}

	virtual std::string getName() {
		return name;
	}


protected:
	std::vector<Piece*> pieces;

private:
	std::string name;
	std::string team;
};

class HumanPlayer : public Player {
	friend class Board;
public:

	HumanPlayer(std::string name_in, std::string team_in) {
		setName(name_in);
		setTeam(team_in);
	}

	//REQUIRES: piece is not a nullptr
	//returns the pointer to the piece that is
	//trying to be found in the given player's pieces vector
	Piece* find(Piece* piece) override {
		for (int i = 0; i < int(pieces.size()); ++i) {
			//if the locations are equal, this is the piece
			//you're looking for since there can only be
			//one piece at a location at a time
			if (piece->getLocation() == pieces[i]->getLocation()) {
				return pieces[i];
			}
		}
		return nullptr;
	}

	//changes the location of the desired piece to the given destination
	void makeMove(Piece *piece, std::string destination) override {
		piece->setLocation(destination);
	}

	//removes the piece from the pieces vector
	void removePiece(Piece* piece) override {
		Piece* piecePtr = find(piece);
		delete piecePtr;
		piecePtr = nullptr;
	}

	~HumanPlayer() {
		//delete every dynamically allocated piece in the pieces vector
		for (int i = 0; i < int(pieces.size()); ++i) {
			delete pieces[i];
		}
	}

private:
	
};

class cpuPlayer : public Player {
	friend class Board;
public:

	cpuPlayer(std::string team_in) {
		setName("cpu");
		setTeam(team_in);
		//push back standard set of starting pieces for given team
	}

	//returns the pointer to the piece that is
	//trying to be found in the given player's pieces vector
	Piece* find(Piece* piece) override {
		for (int i = 0; i < int(pieces.size()); ++i) {
			//if the locations are equal, this is the piece
			//you're looking for since there can only be
			//one piece at a location at a time
			if (piece->getLocation() == pieces[i]->getLocation()) {
				return pieces[i];
			}
		}
		return nullptr;
	}

	//*****Need to create a function to figure out which piece to
	//move and where to move it****
	void makeMove(Piece* piece, std::string destination) override {
		piece->setLocation(destination);
	}

	//removes the piece from the pieces vector
	void removePiece(Piece* piece) override {
		Piece* piecePtr = find(piece);
		delete piecePtr;
		piecePtr = nullptr;
	}

	~cpuPlayer() {
		//delete every dynamically allocated piece in the pieces vector
		for (int i = 0; i < int(pieces.size()); ++i) {
			delete pieces[i];
		}
	}

private:
	
};

Player* Player_factory(std::string &name_in, std::string &team_in, std::string type_in) {
	if (type_in == "human") { return new HumanPlayer(name_in, team_in); }
	return new cpuPlayer(team_in);
}
#endif //