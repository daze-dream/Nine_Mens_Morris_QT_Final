#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QObject>
#include <QDialog>
#include <QDialogButtonBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QListWidget>
#include <QString>
#include <QLabel>
#include <QApplication>
#include <QFrame>
#include <QPushButton>
#include <QGroupBox>
#include <QMessageBox>
#include <QVBoxLayout>


#include "Board.h"
#include "boardpositionwidget.h"
#include "choicesdialog.h"
//! GUI representation of the board.
// TODO: surrender button
class BoardWidget : public QWidget, public Board
{
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = nullptr);
    void togglePhase2At(){this->phase2At = 3 - phase2At;};
    void showDialog(){this->choices->exec();};
private:
    //! holds GUI positions
    BoardPositionWidget positionsW[7][7];
    //! descriptor sidebar
    QListWidget *statusList;
    //! displays the rules, add as necessary
    QListWidget *rules;
    // TODO: add option to play against AI or Human next time
    //! button to reset the board
    QPushButton* reset;
    //! button to surrender
    QPushButton* surrender;
    //! Dialog Box Holding the opponent choices and tools
    QDialog* thing = new QDialog();
    choicesdialog* choices = new  choicesdialog();
    //! updates the statusList with the passed string
    void updateStatusList(QString inc);
    //! interim variable for the "phase 2 states": 1 is selection, 2 is moving.
    int phase2At = 1;
    //! style sheets
    void hoverStyle();
    void selectionStyle();
    void removeStyle();

    //! variables for phase 2 GUI. Represents what is selected
    char rowSelected;
    //! variables for phase 2 GUI. Represents what is selected
    int columnSelected;
    //! variables for phase 2 GUI. Represents goal selected
    char rowGoal;
    //! variables for phase 2 GUI. Represents goal selected
    int  columnGoal;

    //! disable buttons on victory by iterating through them
    void gameOverButtonDisable();
    //! comprehensive AI move to draw on the board
    void AIMoveWidget();

    QWidget* blank = new QWidget();

    QLabel* playerPieceLabel1 = new QLabel(tr("Active Pieces: "));
    QLabel* playerPieceLabel2 = new QLabel(tr("Active Pieces: "));

    QLabel* player1ActivePieceLabel = new QLabel(tr("0"));
    QLabel* player2ActivePieceLabel = new QLabel(tr("0"));


    QLabel* playerMillLabel1 = new QLabel(tr("Mills: "));
    QLabel* playerMillLabel2 = new QLabel(tr("Mills: "));


    QLabel* player1MillLabel = new QLabel(tr("0"));
    QLabel* player2MillLabel = new QLabel(tr("0"));

    QLabel* playerFlightLabel1 = new QLabel(tr("Flight Mode: "));
    QLabel* playerFlightLabel2 = new QLabel(tr("Flight Mode: "));


    QLabel* player1FlightLabel = new QLabel(tr("Off"));
    QLabel* player2FlightLabel = new QLabel(tr("Off"));

    QLabel* currentGamePhase = new QLabel(tr("Phase 1"));
    QLabel* currentPlayerLabel = new QLabel(tr("Turn: Player 1"));
    QMessageBox* gameoverAnnounce = new QMessageBox();


signals:


public slots:
    //! Sort of the driving force of the game. When a position is clicked, this is fired off. Holds most of the GUI logic and ties the game together.
    void posClicked();
    //! Reset the board slot.
    void resetBoardGUI();
    //! Surrender slot.
    void surrenderButtonGUI();

    //! Chocie from the dialog box made
    void choiceSelected(bool choice);



};

#endif // BOARDWIDGET_H
