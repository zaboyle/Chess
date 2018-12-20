#ifndef GAME_H
#define GAME_H

#include<iostream>
#include "board.h"
#include "player.h"

class Game {

    private:
        Board gameBoard;
        Player* player1 = nullptr;
        Player* player2 = nullptr;
        bool player1Turn = false;
        bool player1White = false;

    public:
        //ctor
        Game() {
            printMenu();
            int input = 0;
            std::string file = "";
            std::cin >> input;
            switch (input) {
                case 2:
                    setPlayers();
                    break;
                case 1:
                    std::cout << "Which file would you like to load: ";
                    std::cin >> file;
                    loadGame(file);
                    break;
                default:
                    throw(std::exception());
            }
        }

        //Requires: nothing
        //Modifies: cout, player1 and 2's names and types
        void printMenu() {
            std::cout << "Welcome to Chess!\n\n\n";
            std::cout << "Please enter your choice:\n";
            std::cout << "1) Load Game\n2) New Game\n\n";
        }

        //Requires: a valid file to load from (format TBD)
        //Modifies: the board
        //Effects: puts the board in the state that the file
        //         specifies. Also updates whose turn it is
        void loadGame(std::string game_file) {
            //TODO
        }

        //Requires: the choice was to play a new game
        //Modifies: players names and types
        void setPlayers() {
            //Player1 setup
            std::string name;
            std::cout << "Player 1, enter your name (or 'cpu' for AI): ";
            std::cin >> name;
            if(name == "cpu") { player1 = new AI(); }
            else { player1 = new HumanPlayer(name); }
            //select team (W or B)
            std::cout << "Select which team you would like:\n1)White\n2)Black\n";
            int choice = 0;
            std::cin >> choice;
            if(choice == 1) { player1White = true; player1Turn = true; }
            //==========================================================
            //Player2 setup
            std::cout << "Player 2, enter your name (or 'cpu' for AI): ";
            std::cin >> name;
            if(name == "cpu") { player2 = new AI(); }
            else { player2 = new HumanPlayer(name); }
        }

        //Requires: players have already been chosen
        //Modifies: the board
        //Effects: plays the game. Could either be a new game
        //         or one loaded from a file
        void play() {
            //TODO
            printBoard(std::cout);
        }

        //Requires: a valid output stream
        //Modifies: os
        //Effects: print the board to os
        void printBoard(std::ostream &os) {
	        //print board to os
	        for (int col = 1; col < 9; ++col) {
		        os << "  +----+----+----+----+----+----+----+----+" << std::endl << (9 - col) << " ";
		        for (char row = 'a'; row <= 'h'; ++row) {
                    //access like gameBoard[a][1] -> bottom left square
			        os << "|  ";
                    if(gameBoard[row][col]) { os << gameBoard[row][col]->abbr << " ";}
                    else { os << "  "; }
		        }
		        os << "|" << std::endl;
	        }
	        os << "  +----+----+----+----+----+----+----+----+" << std::endl;
	        os << "     a    b    c    d    e    f    g    h" << std::endl << std::endl;
        }

        //destructor
        ~Game(){
            delete player1;
            delete player2;
            //board dtor will be called automatically
        }
};

#endif //GAME_H
