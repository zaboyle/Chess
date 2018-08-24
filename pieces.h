#ifndef PIECES_H
#define PIECES_H

#include <string>
#include <map>
#include <vector>
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

PIECES AND UNICODE ABBREVIATIONS:
King:
	Black: \u265a
	White: \u2654
Queen:
	Black: \u265b
	White: \u2655
Rook:
	Black: \u265c
	White: \u2656
Bishop:
	Black: \u265d
	White: \u2657
Knight:
	Black: \u265e
	White: \u2658
Pawn:
	Black: \u265f
	White: \u2659
	

Implementation ideas:
- only member variable might be position
- virtual move/take functions <-- should there even be a 'take' function?
- pure virtual base class
- maybe add color to pieces? Aka color the letters displayed
on the board for easier distinciton (see 183 projects for help)
*/
class Piece {

public:

	Piece(std::string abbr_in, int points_in, std::string location_in, std::string team_in) 
		: location({ location_in[0], int(location_in[1]) }), abbreviation(abbr_in), points(points_in), team(team_in) {
	}

	virtual bool validMove(const std::string destination ,std::string team) = 0;

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

	std::string getTeam() {
		return team;
	}

	//returns true if the piece can take an opponent's piece located at destination. 
	//DOES NOT CONSIDER CHECK
	virtual bool validTake(std::string destination, std::string team) {
		//returns true if the piece in question can take an opponent's piece at destination
		//...
		//since pawns are the only pieces that take differently than they move,
		//this code will allow me to only define the function in the Pawn subclass
		//and save some typing
		return true;
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
	std::string team;
	
};

class Pawn : public Piece {
public:
	Pawn(std::string location_in, std::string team_in) : Piece("P", 1, location_in, team_in) {
	}

	//this needs to be here otheriwse it says pawn is an abstract class
	bool validMove(const std::string destination, std::string team) override {
		return false;
	}

	//returns true if the piece is "allowed" to move to the given location
	bool validMove(const std::string destination) { 
		std::pair<char, int> loc = getLocation();

		//pawns can only move forwards. We will deal with taking pieces in the board ADT
		if (destination[0] != loc.first) { return false; }

		if (this->getTeam() == "black") {
			//moving 2 at start of game
			if (loc.second == 7 && int(destination[1]) == (loc.second - 2)) { return true; }
			//pawns can always move 1 ahead
			if (int(destination[1]) == (loc.second - 1)) { return true; }
		}

		if (this->getTeam() == "white") {
			//moving 2 at start of game
			if (loc.second == 2 && int(destination[1]) == (loc.second + 2)) { return true; }
			//pawns can always move 1 spot ahead
			if (int(destination[1]) == (loc.second + 1)) { return true; }

		}
		
		return false;
	}

	virtual bool validTake(std::string destination) {
		std::pair<char, int> loc = getLocation();
		if (this->getTeam() == "black") {
			/*
			black pawns can only take diagonally down
			example:
				+----+----+----+
				|	 |	P |	   |
				+----+----+----+
				|  X |	  |	 X |
				+----+----+----+

			the 'X's mark the places where the pawns can move if there are any opponent's pieces there

			so, the column must be 1 to the left OR right, AND the row must be 1 down
			*/
			if ((loc.first == (destination[0] - 1) || loc.first == (destination[0] + 1)) 
				&& loc.second == (int(destination[1]) - 1)) { return true; }
		}

		/*
		white pawns can only take diagonally up
		example:
		+----+----+----+
		|  X |    |	 X |
		+----+----+----+
		|    |	P |	   |
		+----+----+----+

		the 'X's mark the places where the pawns can move if there are any opponent's pieces there

		so, the column must be 1 to the left OR right, AND the row must be 1 up
		*/
		if (this->getTeam() == "white") {
			if ((loc.first == (destination[0] - 1) || loc.first == (destination[0] + 1))
				&& loc.second == (int(destination[1]) + 1)) {
				return true;
			}
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
	Knight(std::string location_in, std::string team_in) : Piece("KN", 3, location_in, team_in) {}

	bool validMove(const std::string destination, std::string team) override {
		std::pair<char, int> loc = getLocation();

		//all ways to move in an "L" shape on the board
		if(loc.first == (destination[0] - 1) && loc.second == (destination[1] + 2) ||
			loc.first == (destination[0] - 1) && loc.second == (destination[1] - 2) ||
			loc.first == (destination[0] + 1) && loc.second == (destination[1] + 2) ||
			loc.first == (destination[0] + 1) && loc.second == (destination[1] - 2) ||
			loc.first == (destination[0] - 2) && loc.second == (destination[1] + 1) || 
			loc.first == (destination[0] - 2) && loc.second == (destination[1] - 1) ||
			loc.first == (destination[0] + 2) && loc.second == (destination[1] + 1) ||
			loc.first == (destination[0] + 2) && loc.second == (destination[1] - 1)
			) {
			return true;
		}
		return false;
	}

private:
	
};

class Bishop : public Piece {
public:
	Bishop(std::string location_in, std::string team_in) : Piece("B", 3, location_in, team_in) {}

	bool validMove(const std::string destination, std::string team) override {
		std::pair<char, int> loc = getLocation();
		if ((destination[1] - loc.second) == (int(destination[0]) - int(loc.first))) { return true; }
		return false;
	}

private:
	
};

class Rook : public Piece {
public:
	Rook(std::string location_in, std::string team_in) : Piece("R", 5, location_in, team_in) {}

	bool validMove(const std::string destination, std::string team) override {
		std::pair<char, int> loc = getLocation();
		if ((destination[1] == loc.second) || (destination[0] == loc.first)) { return true; }
		return false;
	}

private:

};

class Queen : public Piece {
public:
	Queen(std::string location_in, std::string team_in) : Piece("Q", 9, location_in, team_in) {}

	bool validMove(const std::string destination, std::string team) override { 
		std::pair<char, int> loc = getLocation();
		if ((destination[1] - loc.second) == (int(destination[0]) - int(loc.first))) { return true; }
		if ((destination[1] == loc.second) || (destination[0] == loc.first)) { return true; }
		return false;
	}

private:

};

class King : public Piece {
public:
	King(std::string location_in, std::string team_in) : Piece("K", 0, location_in, team_in) {}

	bool validMove(const std::string destination, std::string team) override { 
		std::pair<char, int> loc = getLocation();

		//4 diagonal spaces
		//2 vertical spaces
		//2 horizontal spaces
		if ((loc.first == (destination[0] - 1) && loc.second == (destination[1] - 1)) ||
			(loc.first == (destination[0] - 1) && loc.second == (destination[1] + 1)) ||
			(loc.first == (destination[0] + 1) && loc.second == (destination[1] - 1)) ||
			(loc.first == (destination[0] + 1) && loc.second == (destination[1] + 1)) ||
			loc.first == (destination[0] + 1) || loc.first == (destination[0] - 1) ||
			loc.second == (destination[1] + 1) || loc.second == (destination[1] - 1)) {
			return true;
		}
		return false;
	}

private:
	
};

bool operator==(std::pair<char, int> &loc1, std::pair<char, int> &loc2) {
	return loc1.first == loc2.first && loc1.second == loc2.second;
}

#endif //