#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

#include <functional>
#include <utility>
#include <tuple>
#include <iostream>


using std::pair;
//! class representing a location on the board
class BoardPosition
{
public:
    BoardPosition();
    BoardPosition(char x, int y);
    void setCoord(char x, int y) { this->coord.first = x; this->coord.second = y; };
    /*! sets the ID of the location*/
    void setStatus(int x) { this->locationStatus = x; };
    void setDisp(char x) { this->locationDisp = x; };
    void setIsMill(bool x) { this->partOfMill = x; };
    /*! sets up the locations X and Y pair,
        \the ID,
        \what should be displayed,
        \and if it is a valid move to differentiate from non-existant locations
    */
    /*! additional setup besides constructor so undesired locaitons can be locked out*/
    void setup(char x, int y, int status, char display, bool valid);
    /*! gets the "display" of the board, used for commandline*/
    char getDisp() { return this->locationDisp; };
    /*! gets the ID of the player who owns it. Returns 1, 2 or 0 */
    int getStatus() { return this->locationStatus; };
    /*! gets the pair of coord. Remember that first[a-z] and second[1-7] so be careful with data structures*/
    pair<char, int> getCoord() { return this->coord; };
    /*! used to set the middle location as a terminating spot for move validation looking */
    void setTerminator(bool x) { this->terminateSpot = x; };
    /*! get if the location is the middle or not*/
    bool getTerminator() { return this->terminateSpot; };
    /*! set if the location is a valid place to place a piece */
    void setValid(bool x) { this->isValid = x; };
    /*! getter for if it is a valid board location */
    bool isItValid() { return this->isValid; };
    /*! this just returns the member variable, does not do a check*/
    bool isPartofMill() { return this->partOfMill; };
    /*! iterates through the passed through board and determines if it is in a mill.
     *  used to dynamically know if it is in a mill
    */
    bool checkIfPartOfMill(BoardPosition positions[][7]);
private:
    /*! the coordinate of the location. Remember that first[a-z] and second[1-7] so be careful with data structures*/
    pair<char, int> coord = std::make_pair('0',0);
    /*! player ID of location. 0 means empty, 3 means connector.*/
    int locationStatus = 0;
    /*! what to display to console.*/
    char locationDisp = ' ';
    /*! if it is a valid place to place a move */
    bool isValid = false;
    /*! Quick variable set if it it made a mil */
    bool partOfMill = false;
    /*! special case to stop the search for the middle section */
    bool terminateSpot = false;
    /*! offset for ASCII conversion */
    int offset = 97;
};

#endif // BOARDPOSITION_H
