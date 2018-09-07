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

	Player(std::string name_in, std::string team_in) : name(name_in), team(team_in) {
	}

	//finds the player's piece at the given destination. If
	//the player does not own a piece at that location, returns nullptr
	virtual Piece* findByLocation(std::string location) {
		std::pair<char, int> position = {location[0], (location[1] - 48)};
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

	void addPiece(Piece* piece_in) {
		pieces.push_back(piece_in);
	}

	//removes the piece from the pieces vector
	void removePiece(std::string location) {
		Piece* piecePtr = findByLocation(location);
		delete piecePtr;
		piecePtr = nullptr;
	}

	~ Player() {
		//delete every dynamically allocated piece in the pieces vector
		while (!pieces.empty()) {
			pieces.pop_back();
		}
	}

	void setTeam(std::string team_in) {
		team = team_in;
	}

	std::string getTeam() {
		return team;
	}

	void setName(std::string name_in) {
		name = name_in;
	}

	std::string getName() {
		return name;
	}

//removed this because of difficulties in copy ctors
//protected:
	std::vector<Piece*> pieces;

private:
	std::string name;
	std::string team;
};

class HumanPlayer : public Player {
	friend class Board;
public:

	HumanPlayer(std::string name_in, std::string team_in) : Player(name_in, team_in) {
	}

	//copy ctor
	HumanPlayer(Player* player_in) : Player(player_in->getName(), player_in->getTeam()) {
		for (Piece* p : player_in->pieces) {
			if (p->getAbbr() == "P") {
				Piece* pawn(p);
				this->pieces.push_back(pawn);
			}
			else if (p->getAbbr() == "N") {
				Piece* knight(p);
				this->pieces.push_back(knight);
			}
			else if (p->getAbbr() == "B") {
				Piece* bishop(p);
				this->pieces.push_back(bishop);
			}
			else if (p->getAbbr() == "R") {
				Piece* rook(p);
				this->pieces.push_back(rook);
			}
			else if (p->getAbbr() == "Q") {
				Piece* queen(p);
				this->pieces.push_back(queen);
			}
			else if (p->getAbbr() == "K") {
				Piece* king(p);
				this->pieces.push_back(king);
			}
		}
		/*
		this->setName(player_in->getName());
		this->setTeam(player_in->getTeam());
		*/
	}

	//changes the location of the desired piece to the given destination
	void makeMove(std::string piece_start_loc, std::string piece_destination) override {
		Piece* piece = this->findByLocation(piece_start_loc);
		piece->setLocation(piece_destination);
	}

	~HumanPlayer() {
		//I don't think this is necessary since this is the code for the general player class

		/*delete every dynamically allocated piece in the pieces vector
		for (int i = 0; i < int(pieces.size()); ++i) {
			delete pieces[i];
		}
		*/
	}

private:
	
};

class cpuPlayer : public Player {
	friend class Board;
public:

	cpuPlayer(std::string team_in) : Player("cpu", team_in) {
	}

	cpuPlayer(Player* player_in) : Player(player_in->getName(), player_in->getTeam()) {
		for (Piece* p : player_in->pieces) {
			if (p->getAbbr() == "P") {
				Piece* pawn(p);
				this->pieces.push_back(pawn);
			}
			else if (p->getAbbr() == "N") {
				Piece* knight(p);
				this->pieces.push_back(knight);
			}
			else if (p->getAbbr() == "B") {
				Piece* bishop(p);
				this->pieces.push_back(bishop);
			}
			else if (p->getAbbr() == "R") {
				Piece* rook(p);
				this->pieces.push_back(rook);
			}
			else if (p->getAbbr() == "Q") {
				Piece* queen(p);
				this->pieces.push_back(queen);
			}
			else if (p->getAbbr() == "K") {
				Piece* king(p);
				this->pieces.push_back(king);
			}
		}
		//this->setTeam(player_in->getTeam());
	}

	//*****Need to create a function to figure out which piece to
	//move and where to move it****
	void makeMove(std::string piece_start_loc, std::string piece_destination) override {
		Piece* piece = this->findByLocation(piece_start_loc);
		piece->setLocation(piece_destination);
	}

	~cpuPlayer() {
		//I don't think this is necessary since this is the code for the general player class

		/*delete every dynamically allocated piece in the pieces vector
		for (int i = 0; i < int(pieces.size()); ++i) {
			delete pieces[i];
		}
		*/
	}

private:
	
};
#endif //