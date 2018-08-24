#include<iostream>
#include "board.h"
//#include "pieces.h"
//#include "player.h"
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

/* this overloaded operator must be above the 'play'
   function due to compile reasons. This operator
   prints the board to the console in the given format
   with pieces represented as their symbols
*/
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

//define game ADT here//
class Game {
public:
	Game(std::string gameType, Player* player1_in, Player* player2_in) : gameBoard(Board(player1_in, player2_in)) {
		if (player1_in->getTeam() == "white") { upNext = player1_in; }
		else if(player2_in->getTeam() == "white"){ upNext = player2_in; }
	}
	
	//game is over when one player is in checkmate
	bool over() {
		return gameBoard.isCheckmate(gameBoard.getPlayer1()) 
			|| gameBoard.isCheckmate(gameBoard.getPlayer2());
	}

	void play() {

		std::cout << "Use the following format to enter moves:\n";
		std::cout << "<location of piece you wish to move> <destination you wish to move to>\n";
		std::cout << "This program assumes you enter moves in the correct format. If your move is illegal, players will be prompted until a valid move is given\n\n\n";

		while(!this->over()) {
			//teams and board - already done
			std::cout << gameBoard;
			//get input from user
			std::string start_loc, end_loc;
			std::cout << upNext->getName() + ", enter move: ";
			std::cin >> start_loc >> end_loc;
			
			while(!gameBoard.legalMove(upNext, start_loc, end_loc)) {
				//cout you cant do that
				std::cout << "Sorry, that was an invalid move. Please enter a legal move:";
				std::cin >> start_loc >> end_loc;
			}

			//announcing where each move
			std::cout << "\n" + upNext->getName() + "'s move:\n";
			std::cout << "\n" + upNext->findByLocation(start_loc)->getAbbr() + " to " + end_loc + "\n";
			
			gameBoard.movePiece(upNext, start_loc, end_loc);

			//go until someone is in checkmate (or presses 's' or 'q'?)
		}

		std::cout << gameBoard;

		Player* winner = nullptr;
		if (gameBoard.isCheckmate(gameBoard.getPlayer1())) { winner = gameBoard.getPlayer2(); }
		else { winner = gameBoard.getPlayer1(); }

		char icons[13] = { '\u2659', '\u2658', '\u2657', '\u2656', '\u2655', '\u2654', '\u265a', '\u265b', '\u265c', '\u265d', '\u265e', '\u265f'};

		std::cout << "\n\n\n" << icons << "\n==============================\n";
		std::cout << "Congratulations, " + winner->getName() + "! You won!";

	}

private:
	Board gameBoard;
	Player* upNext;
};


void printHeader() {
	std::cout << "==============================\n";
	std::cout << "Welcome to Chess by Zach Boyle\n";
	std::cout<< "==============================\n\n";
}

void printGameOptions() {
	std::cout << "Play a new game? or load an old one?\n\n";
	std::cout << "1: New Game\n";
	std::cout << "2: Load Game\n";
}

std::string getGameType() {
	printGameOptions();
	std::string gameInput = "";
	std::cin >> gameInput;
	while (gameInput != "1" && gameInput != "2") {
		std::cout << "Sorry, that input isn't valid\n";
		printGameOptions();
		std::cin >> gameInput;
	}
	if (gameInput == "1") { return "new"; }
	return "load";
}

void printPlayerOptions() {
	std::cout << "How would you like to play?\n";
	std::cout << "\n1: Human v Human\n";
	std::cout << "2: Human v CPU\n";
	std::cout << "3: CPU v CPU\n";
}

Player* Player_factory(std::string &name_in, std::string &team_in, std::string type_in) {
	if (type_in == "human") { return new HumanPlayer(name_in, team_in); }
	return new cpuPlayer(team_in);
}

std::pair<std::string, std::string> getPlayerTypes() {
	printPlayerOptions();
	std::string input = "";
	std::cin >> input;
	while (input != "1" && input != "2" && input != "3") {
		std::cout << "Sorry, that input isn't valid\n";
		printPlayerOptions();
		std::cin >> input;
	}
	if (input == "1") { return { "human", "human" }; }
	else if (input == "2") { return { "human", "cpu" }; }
	return { "cpu", "cpu" };
}

std::pair<Player*, Player*> makeTeams(std::pair<std::string, std::string> playerTypes_in) {
	std::string player1Type = playerTypes_in.first;
	std::string player2Type = playerTypes_in.second;
	std::string player1Name = "";
	std::string player1Team = "";
	std::string player2Name = "";
	std::string player2Team = "";
	Player* player1Ptr = nullptr;
	Player* player2Ptr = nullptr;
	if (player1Type == "human" && player2Type == "human") {
		std::cout << "\nPlayer 1, please enter your name:\n";
		std::cin >> player1Name;
		std::cout << player1Name << ", please enter your preferred team (white or black):\n";
		std::cin >> player1Team;
		while (player1Team != "white" && player1Team != "black") {
			std::cout << "please enter either 'white' or 'black' as your preferred team\n";
			std::cin >> player1Team;
		}
		std::cout << "\nPlayer 2, please enter your name:\n";
		std::cin >> player2Name;
		if (player1Team == "white") { player2Team = "black"; }
		else if (player1Team == "black") { player2Team = "white"; }
		std::cout << player2Name << ", your team is " << player2Team << "\n\n";

	} 
	else if (player1Type == "human" && player2Type == "cpu") {
		std::cout << "Player 1, please enter your name:\n";
		std::cin >> player1Name;
		std::cout << player1Name << ", please enter your preferred team (white or black):\n";
		std::cin >> player1Team;
		while (player1Team != "white" && player1Team != "black") {
			std::cout << "please enter either 'white' or 'black' as your preferred team\n";
			std::cin >> player1Team;
		}
		if (player1Team == "white") { player2Team = "black"; }
		else if (player1Team == "black") { player2Team = "white"; }
		player2Name = "cpu";
		std::cout << "The cpu will be " << player2Team << "\n\n";
	}
	else {
		player1Team = "white";
		player2Team = "black";
		player1Name = "cpu1";
		player2Name = "cpu2";
		std::cout << "\ncpu1's team is white\ncpu2's team is black\n\n";
	}

	player1Ptr = Player_factory(player1Name, player1Team, player1Type);
	player2Ptr = Player_factory(player2Name, player2Team, player2Type);
	return { player1Ptr, player2Ptr };
}



int main() {
	//ask for HvH, CPUvH, or CPUvCPU
	//ask for white or black
	printHeader();
	std::string gameType = getGameType();
	if (gameType == "new") {
		// do something w/ player initialization and start new game
		std::pair<std::string, std::string> playerTypes = getPlayerTypes();
		std::pair<Player*, Player*> players = makeTeams(playerTypes);
		Player* player1 = players.first;
		Player* player2 = players.second;
		Game game("new", player1, player2);
		game.play();
	} 
	else {
		//do something w/ loading games
		//implement loading stuff
		std::cout << "working on it";
	}
	return 0;
}