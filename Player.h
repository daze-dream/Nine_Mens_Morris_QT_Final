#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Enum.h"
#include "BoardPosition.h"
#include <cstdlib>
#include <ctime>
#include <random>

using std::vector;
using std::string;
//! Player class. Holds all the info and functions for a player, and if they are an AI or not
class Player
{
public:
    //! default constructor
    Player();
    //! normal constructor
    Player(int id, bool isAI);
    //! gets ID
    int getPlayerID() { return playerID; };
    //! gets if they are AI
    bool getIsAI() { return isAI; };
    //! gets phase 1 pieces
    int getPhase1Pieces() { return phase1Pieces; };
    //! gets phase 2 pieces, and main pieces of the game
    int getPhase2Pieces() { return phase2Pieces; };
    //! get if in flight
    bool getFlight() { return isFlight; };
    //! get active mills
    int getActiveMills() { return this->activeMills; };
    //! get stable mills
    int getStableMills() {return this->stableMills;};
    //! returns their enemy. Remember it is 1 or 2, be careful for accessing data structures
    int getEnemy() { return 3 - this->playerID; };
    //! gets the free spaces
    int getFreePieces() {return this->freePieces;}


    //! sets player ID
    void setID(int id) { this->playerID = id; };
    //! sets if they are AI
    void setAI(bool isAI) { this->isAI = isAI; };
    //! sets phase 1 pieces
    void setPhase1Pieces(int x) { this->phase1Pieces = x; };
    //! sets phase 2 pieces
    void setPhase2Pieces(int x) { this->phase2Pieces = x; };
    //! set flight mode
    void setFlight(bool flight) { this->isFlight = flight; };
    //! set active mills
    void setActiveMills(int x) { this->activeMills = x; };
    //! set stable mills
    void setStableMills(int x) {this->stableMills += x;}
    //! sets free pieces
    void setFreePieces(int x){this->freePieces = x; }
    //functions

    //! player check called after mill phase, and toggles if they are ready to leave the nest.
    void timetoFly();
    //! subtracts phase 2 pieces
    void subtractPhase2Too() { this->phase2Pieces--; }
    //! subtracts pieces depending on game state, but mainly for phase 1
    void subtractPiece(GameStates state);
    //! add a piece. Only really applies to phase 2 so no need to pass state.
    void addPiece();
    //! decrement active mills
    void subtractMills() { this->activeMills--; };
    //! decrement stable mills
    void subtractMillsStable(){this->stableMills--;}
    //! for AI, sort of, for Phase 1
    string getRandomMove(vector<string> moves);
    //! for AI, get a location to move to
    string getRandomMovePhase2Goal(vector<string> moves);
    //! for AI, get an enemy piece DONE
    string getRandomEnemyPiece(vector<string> moves);
    //! for AI, gets a piece the player owns DONE
    string getRandomPieceIOwn(vector<string> moves);
    //! for AI, combines two functions and returns a pair
    pair<string, string> getRandomPhase2Move(vector<string> moves);
    //! Increments free pieces
    void increaseFreePieces(){this->freePieces++;}
    //! decrements free pieces, for piece removal;
    void decreaseFreePieces(){this->freePieces--; if(freePieces<0) freePieces=0;}
    //! Restores free pieces after a phase 2 move breaks a mill.
    void restoreFreePieces();
    //! Called when mill is made
    /*!
      subtracts 3 pieces from free pieces variable. If it is below 0, set it to 0.
      used to determine if you cn capture a piece in a mill
    */
    bool updateFreePieces();




private:
    //! player ID
    int playerID = 0;
    //! if they are an AI
    bool isAI = false;
    // phase 1 pieces, or a counter for pieces to place
    int phase1Pieces = 9;
    //! phase 2 pieces, or a counter for how many pieces they actually have left
    int phase2Pieces = 0;
    //! flight mode occuers when phase2Pieces < 3. lifts movement restriction
    bool isFlight = false;
    //! active mills are mills that have just been created, and still have pieces to remove
    int activeMills = 0;
    //! stable mills are mills that have been made and are not active.
    int stableMills = 0;
    //! variable indicating how many "available" pieces there are, aka not in mill. Can't go below 0, function takes care of that
    int freePieces = 0;




};
#endif // PLAYER_H
