#include "Player.h"

Player::Player()
{
}

Player::Player(int id, bool isAI)
{
    this->playerID = id;
    this->isAI = isAI;
    if(isAI)
    {
        srand(time(NULL));
    }
}

void Player::timetoFly()
{
    if (this->getPhase2Pieces() <= 3)
    {
        setFlight(true);
    }
}

void Player::subtractPiece(GameStates state)
{
    switch (state) {
    case phase1:
        this->phase1Pieces--;
        break;
    case phase2:
        this->phase2Pieces--;
        break;
    }
}

void Player::addPiece()
{
    this->phase2Pieces++;
}

std::string Player::getRandomMove(vector<std::string> moves)
{
    string toReturn;
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    int x  = dist(thing);
    toReturn = moves.at(x);
    return toReturn;
}

std::string Player::getRandomMovePhase2Goal(vector<std::string> moves)
{
    string toReturn;
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    int x  = dist(thing);
    toReturn = moves.at(x);
    return toReturn;
}

std::string Player::getRandomEnemyPiece(vector<std::string> moves)
{
    string toReturn;
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    int x  = dist(thing);
    toReturn = moves.at(x);
    return toReturn;

}

std::string Player::getRandomPieceIOwn(vector<std::string> moves)
{
    string toReturn;
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(0, moves.size() - 1);
    int x  = dist(thing);
    toReturn = moves.at(x);
    return toReturn;
}

pair<std::string, std::string> Player::getRandomPhase2Move(vector<std::string> moves)
{
    return std::make_pair("x", "x");
}

void Player::restoreFreePieces()
{
    if(phase2Pieces%3 == 0)
    {
        freePieces+=3;
    }
    else
    {
        freePieces+=2;
    }

}

bool Player::updateFreePieces()
{
    bool belowZero = false;
    this->freePieces-=3;
    if(freePieces < 3)
    {
        freePieces = 0;
        belowZero = true;
    }
    return belowZero;
}
