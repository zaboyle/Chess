#ifndef GAME_H
#define GAME_H

#include<iostream>
#include <fstream>
#include <stdio.h>
#include "board.h"
#include "player.h"
#include "termcolor.hpp"

class Game {

    private:
        Board gameBoard;
        Player* player1 = nullptr;
        Player* player2 = nullptr;
        bool player1Turn = false;
        bool player1White = false;

    public:
        //ctor
        //starts the game. asks for new game or load game.
        //sets up the game accordingly
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

        //Requires: players have already been chosen
        //Modifies: the board
        //Effects: plays the game. Could either be a new game
        //         or one loaded from a file
        void play() {
            //TODO

            

            //at the end of each turn
            printBoard(std::cout);
        }

        //destructor
        ~Game(){
            delete player1;
            delete player2;
            //board dtor will be called automatically
        }

    //the functions below need only be used by the Game class
    //and should not be used outside of it
    private:
        //Requires: nothing
        //Modifies: cout, player1 and 2's names and types
        //Effects: determines whether to do a load or new game
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
            //TODO:
            //could also use try/catch and while
            //for invalid file names
            
            //file format:
            /*
            <p1_name>
            <p2_name>
            <p1 turn (0 or 1)>
            <p1 white (0 or 1)>
            # things with '#' are comments here, and will not appear in the file
            # symbols of the pieces in their corresponding squares
            # 'X' denotes nullptr
            # starts with 'upper left corner' of board (a8) and goes to h8, then
            # down. aka, it follows the pattern outlined in board.h
            # ****uppercase for white, lowercase for black****
            # example: 
            r n b q k b X r
            p p p p X p p X
            X X X X X n X p
            X X X X p X X X
            X X X X X X X X
            X X X P B X X X
            P P P X P P P P
            R N X Q K B N R
            */
           //set the players based on their names
            std::string input;
            std::getline(std::cin, input);
            if(input == "cpu") { player1 = new AI(); }
            else { player1 = new HumanPlayer(input); }
            std::getline(std::cin, input);
            if(input == "cpu") { player2 = new AI(); }
            else { player2 = new HumanPlayer(input); }

            //set whose turn it is and colors
            std::cin >> player1Turn >>player1White;

            //set up the board
            for(int col = 1; col < 9; ++col) {
                for(int row = 'a'; row <= 'h'; ++row) {
                    //clear anything that the pointer 
                    //is pointing at (from default ctor)
                    delete gameBoard[row][col];

                    char piece;
                    std::cin >> piece;
                    switch (piece) {
                        case 'X':
                            gameBoard[row][col] = nullptr;
                            break;
                        case 'P':
                            gameBoard[row][col] = new Pawn(Team::white);
                            break;
                        case 'N':
                            gameBoard[row][col] = new Knight(Team::white);
                            break;
                        case 'B':
                            gameBoard[row][col] = new Bishop(Team::white);
                            break;
                        case 'R':
                            gameBoard[row][col] = new Rook(Team::white);
                            break;
                        case 'Q':
                            gameBoard[row][col] = new Queen(Team::white);
                            break;
                        case 'K':
                            gameBoard[row][col] = new King(Team::white);
                            break;
                        case 'p':
                            gameBoard[row][col] = new Pawn(Team::black);
                            break;
                        case 'n':
                            gameBoard[row][col] = new Knight(Team::black);
                            break;
                        case 'b':
                            gameBoard[row][col] = new Bishop(Team::black);
                            break;
                        case 'r':
                            gameBoard[row][col] = new Rook(Team::black);
                            break;
                        case 'q':
                            gameBoard[row][col] = new Queen(Team::black);
                            break;
                        case 'k':
                            gameBoard[row][col] = new King(Team::black);
                            break;
                        default:
                            std::cerr << "Error: load file incorrect\n";
                            exit(1);
                            break;
                    } //switch
                } //for (letters)
            }//for (numbers)
        }
        
        //Requires: the game is in progress (1+ moves have been made)
        //Modifies: the save file
        //Effects: saves the game to a file. prompts the user for the name
        //         of the save file. Terminates the program afterwards
        void saveGame() {
            //TODO
            std::string saveFilename = "";
            std::cout << "\n\nWhat would you like to name your save file?: ";
            std::cin >> saveFilename;
            //append a .txt extension
            saveFilename += ".txt";
            std::ofstream saveFile;
            saveFile.open(saveFilename);
            //write both players' names
            saveFile << player1->getName() << "\n" << player2->getName() << "\n";
            //write info on teams and turns
            saveFile << player1Turn << "\n" << player1White << "\n";
            //write the board info
            for(int col = 1; col < 9; ++col) {
                for(int row = 'a'; row <= 'h'; ++row) {
                    //if no piece at this location
                    if(!gameBoard[row][col]) { saveFile << "X "; }
                    //if there is a piece at this location
                    else {
                        //uppercase for white pieces
                        if(gameBoard[row][col]->team == Team::white) {
                            saveFile << gameBoard[row][col]->abbr << " ";
                        }
                        //lowercase for black pieces
                        else {
                            saveFile << std::tolower(gameBoard[row][col]->abbr) << " ";
                        }
                    }
                }
                //separate lines
                saveFile << "\n";
            }
            //close the file for writing
            saveFile.close();

            //file save confirmation
            std::cout << "\n\nFile successfully saved to " << saveFilename;
            std::cout << "\nThanks for playing!\n";
            exit(0);
        }

        //Requires: the choice was to play a new game
        //Modifies: players names and types
        //Effects: sets the players' names, who goes first, and teams
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

};

#endif //GAME_H
