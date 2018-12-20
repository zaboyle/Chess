#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {

private:
    std::string name;

public:
    //default ctor
    Player() {}
        
    std::string getName() { return name; }

    void setName(std::string name_in) { name = name_in; }

        //set any future virtual functions = 0
};

class HumanPlayer : public Player {
    //define functions in here for making moves
    //just pass in the board by reference, and make the change.
    //it will be reflected on the game's board
public: 
    HumanPlayer(std::string name_in) { setName(name_in); }

};

class AI : public Player {

public:
    AI() { setName("cpu"); }

};

#endif //