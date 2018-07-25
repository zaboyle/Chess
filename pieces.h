#ifndef PIECES_H
#define PIECES_H

#include <string>
#include <map>
/*

////MAKE 'PIECE' ADT////

- polymorphic
- list of all pieces w/ points and abbreviation:
- pawn, 1, P
- knight, 3, KN
- bishop, 3, B
- rook, 5, R
- queen, 9, Q
- king,  n/a, K

Implementation ideas:
- only member variable might be position
- virtual move/take functions <-- should there even be a 'take' function?
- pure virtual base class
- maybe add color to pieces? Aka color the letters displayed
on the board for easier distinciton (see 183 projects for help)
*/
class Piece {
public:

	Piece(std::string abbr_in, int points_in, std::string location_in) {
		abbreviation = abbr_in;
		points = points_in;
		location = { location_in[0], int(location_in[1]) };
	}

	virtual bool validMove(const std::string destination) = 0;

	//returns the abbreviation of the given piece
	virtual std::string getAbbr() {
		return abbreviation;
	}

	void setAbbr(std::string abbr_in) {
		abbreviation = abbr_in;
	}

	//returns the points the piece is worth
	virtual int getPoints() {
		return points;
	}

	void setPoints(int points_in) {
		points = points_in;
	}

	//returns the location of the piece
	virtual std::pair<char, int> getLocation() {
		return location;
	}

	void setLocation(std::string location_in) {
		location.first = location_in[0];
		location.second = int(location_in[1]);
	}

private:
	//row, col of where the piece is located
	//must be within the bounds of the board
	//form of <letter, num>
	//reminder: access pair with .first and .second
	std::pair<char, int> location;
	//the symbol for the piece
	std::string abbreviation;
	//number of points the piece is worth
	int points;
};

class Pawn : public Piece {
public:
	Pawn(std::string location_in) : Piece("P", 1, location_in) {
	}

	//this needs to be here otheriwse it says pawn is an abstract class
	bool validMove(const std::string destination) override {
		return false;
	}

	//returns true if the piece is "allowed" to move to the given location
	bool validMove(const std::string destination, std::string team) { 
		std::pair<char, int> loc = getLocation();

		//pawns can only move forwards. We will deal with taking pieces in the board ADT
		if (destination[0] != loc.first) { return false; }

		if (team == "black") {
			//moving 2 at start of game
			if (loc.second == 7 && int(destination[1]) == (loc.second - 2)) { return true; }
			//pawns can always move 1 ahead
			if (int(destination[1]) == (loc.second - 1)) { return true; }
		}

		if (team == "white") {
			//moving 2 at start of game
			if (loc.second == 2 && int(destination[1]) == (loc.second + 2)) { return true; }
			//pawns can always move 1 spot ahead
			if (int(destination[1]) == (loc.second + 1)) { return true; }

		}
		
		return false;
	}

	//promotes the pawn to a queen
	void promote() {
		/*
		std::string loc = this->getLocation.first() + std::stoi(this->getLocation.second());
		delete this;
		this = new Queen(loc);
		*/
		//can't assign queen ptr to pawn ptr
	}

private:
	
};

class Knight : public Piece {
public:
	Knight(std::string location_in) : Piece("KN", 3, location_in) {}

	bool validMove(const std::string destination) override { 
		return false;
	}

private:
	
};

class Bishop : public Piece {
public:
	Bishop(std::string location_in) : Piece("B", 3, location_in) {}

	bool validMove(const std::string destination) override { 
		return false;
	}

private:
	
};

class Rook : public Piece {
public:
	Rook(std::string location_in) : Piece("R", 5, location_in) {}

	bool validMove(const std::string destination) override { 
		return false;
	}

private:

};

class Queen : public Piece {
public:
	Queen(std::string location_in) : Piece("Q", 9, location_in) {}

	bool validMove(const std::string destination) override { 
		return false;
	}

private:

};

class King : public Piece {
public:
	King(std::string location_in) : Piece("K", 0, location_in) {}

	bool validMove(const std::string destination) override { 
		return false;
	}

private:
	
};

bool operator==(std::pair<char, int> &loc1, std::pair<char, int> &loc2) {
	return loc1.first == loc2.first && loc1.second == loc2.second;
}

#endif //