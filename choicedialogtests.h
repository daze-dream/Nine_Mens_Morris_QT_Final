#ifndef CHOICEDIALOGTESTS_H
#define CHOICEDIALOGTESTS_H
#include <random>

class choiceDialogTests
{
public:
    choiceDialogTests();
    //emulates the choiceDialog box
    int flipCoin()
    {
        std::random_device rd;
        std::mt19937 thing(rd());
        std::uniform_int_distribution<int> dist(1, 2);


        int x  = dist(thing);
        if(x == 1)
        {
            return 1;
        }
        else
        {
            return 2;
        }

    }

    int randomInteger()
    {

        std::random_device rd;
        std::mt19937 thing(rd());
        std::uniform_int_distribution<int> dist(0, 100);
        int x  = dist(thing);
        return x;
    }
};

#endif // CHOICEDIALOGTESTS_H
