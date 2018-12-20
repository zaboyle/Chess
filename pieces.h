#ifndef PIECES_H
#define PIECES_H

#include <limits>

enum class Team { black = false, white = true };

using infinity = std::numeric_limits<int>;

/*
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
*/

class Piece {

public:

	//put headers of virtual functions = 0 here

	char abbr;
	int points;
	Team team;
};

class Pawn : public Piece {
	
public:

	Pawn(Team team_in) { abbr = 'P'; points = 1; team = team_in;}

};

class Knight : public Piece {
	
public:

	Knight(Team team_in) { abbr = 'N'; points = 3; team = team_in; }

};

class Bishop : public Piece {
	
public:

	Bishop(Team team_in) { abbr = 'B'; points = 3; team = team_in; }

};

class Rook : public Piece {
	
public:

	Rook(Team team_in) { abbr = 'R'; points = 5; team = team_in;}

};

class Queen : public Piece {
	
public:

	Queen(Team team_in) { abbr = 'Q'; points = 9; team = team_in;}

};

class King : public Piece {
	
public:

	King(Team team_in) { abbr = 'K'; points = infinity::infinity(); team = team_in; }

};

#endif //