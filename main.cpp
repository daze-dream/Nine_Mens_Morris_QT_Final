#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "mainwindow.h"
#include <QApplication>
#include "boardwidget.h"
#include "manualtests.h"


//Idea for better mills to fix 5 pieces 2 mills + 1 more piece: store each move made into a player data structure. After every move do a mill check on their
// data structure and set each location's internal data. This will either need a mill vector, or a "free pieces" variable that determines if a piece outside
// of a mill can be captured.

// every time you place a piece, add one to "free piece" variable. When a mill is made, subtract 3 from "free piece," minimum of 0. When capturing a mill piece,
// if freepiece > 0, it is not valid.

int main(int argc, char *argv[])
{
    //unit tests with Catch
    int result = Catch::Session().run(argc,argv);

    //Manual Tests by Alec
    manualTests t;
    //Really only valid for the command-line version
    //t.doAllTests();
    QApplication a(argc, argv);
    BoardWidget b;
    b.show();
    b.showDialog();

    return a.exec();
}
