#ifndef PLAYER_H
#define PLAYER_H
#include "pieces.h"
//#include <string>
//#include <vector>
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
	virtual Piece* findByLocation(std::string location) {
		std::pair<char, int> position = std::pair<char, int>(location[0], location[1] - 97);
		for (Piece* p : pieces) {
			//using my self-defined equality operator
			if (p->getLocation() == position) {
				return p;
			}
		}
		return nullptr;
	}

	Piece* getKing() {
		for (auto iter = pieces.begin(); iter < pieces.end(); ++iter) {
			if ((*iter)->getAbbr() == "K") { return *iter; }
		}
	}

	virtual void makeMove(std::string piece_start_loc, std::string piece_destination) = 0;

	virtual void addPiece(Piece* piece_in) {
		pieces.push_back(piece_in);
	}

	virtual void removePiece(std::string location) = 0;

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

	//changes the location of the desired piece to the given destination
	void makeMove(std::string piece_start_loc, std::string piece_destination) override {
		Piece* piece = this->findByLocation(piece_start_loc);
		piece->setLocation(piece_destination);
	}

	//removes the piece from the pieces vector
	void removePiece(std::string location) override {
		Piece* piecePtr = findByLocation(location);
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

	//*****Need to create a function to figure out which piece to
	//move and where to move it****
	void makeMove(std::string piece_start_loc, std::string piece_destination) override {
		Piece* piece = this->findByLocation(piece_start_loc);
		piece->setLocation(piece_destination);
	}

	//removes the piece from the pieces vector
	void removePiece(std::string location) override {
		Piece* piecePtr = findByLocation(location);
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
#endif //