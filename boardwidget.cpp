#include "boardwidget.h"

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("Nine Men's Morris by Not_Devs: Sprint 3");
    this->setStyleSheet("background-color: gray;");


    Player player1(1, false);
    Player player2(2, true);
    addPlayers(player1);
    addPlayers(player2);
    setState(phase1);
    setCurrPlayerVar(1);
    QGridLayout *boardlayout = new QGridLayout();

    QGridLayout *statusLayout = new QGridLayout();
    QGridLayout *rulelayout = new QGridLayout();
    QGridLayout *newStatusLayout = new QGridLayout();

    rules = new QListWidget;
    rules->setWordWrap(true);
    rules->insertItem(0,tr("Welcome to Nine Men's Morris \n"
                      "Rules: \n"
                      " 1. Each player begins with 9 pieces. \n"
                      " 2. There are two game phases. \n"
                      "     - in Phase 1, players take turns placing pieces on empty spots on the board. This goes on until each player has placed all 9 pieces. \n"
                      "     - in Phase 2, players move their pieces to adjacent locations \n"
                      " 3. When a player successfully places 3 pieces connected by an unbroken line, a player may remove one of their opponent's pieces \n"
                      "     - a piece may only be removed if it is either not part of a mill, or if there are no other possible choices \n"
                      " 4. When a player is reduced to only three pieces, they enter flight mode, and can freely move their pieces, unconstrained by Phase 2's rules. \n"
                      " 5. The game ends when one player is reduced to less than 3 pieces, or no other legal moves can be made. \n"));
    rules->setStyleSheet("background-color:white");

    QSpacerItem *spacer2 = new QSpacerItem(50,100);
    QLabel* title = new QLabel(tr("NINE MEN'S MORRIS"));

    statusList = new QListWidget;
    statusList->setStyleSheet("background-color: white");
    statusList->setWordWrap(true);
    statusList->insertItem(0,tr("Nine Men's Morris Version S2.0 Beta || Group Not_Devs "));
    statusLayout->addWidget(statusList, 5, 0, 1, 2);
    rulelayout->addWidget(rules, 0, 1 ,1, 2 );

    boardlayout->setSpacing(0);
    //start setting up the locations
    // ring 3
    for (char i = 'a'; i < 'h'; i+=3)
    {
        for (int j = 0; j < 7; j += 3)
        {
            positions[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            //adds the button to the widget array and creates a button
            positionsW[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            positionsW[i - asciiOffset][j].setFixedSize(50,50);
            //needed for stylesheet
            positionsW[i - asciiOffset][j].setObjectName("empty");
            connect(&positionsW[i - asciiOffset][j], SIGNAL(clicked()),this,SLOT(posClicked()));

            boardlayout->addWidget(&positionsW[i - asciiOffset][j],j +1, (i - asciiOffset) +1);

        }
    }

    // ring 2
    for (char i = 'b'; i < 'g'; i += 2)
    {
        for (int j = 1; j < 6; j += 2)
        {
            positions[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            //adds the button to the widget array and creates a button
            positionsW[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            positionsW[i - asciiOffset][j].setFixedSize(50,50);
            //needed for stylesheet
            positionsW[i - asciiOffset][j].setObjectName("empty");
            connect(&positionsW[i - asciiOffset][j], SIGNAL(clicked()),this,SLOT(posClicked()));

            boardlayout->addWidget(&positionsW[i - asciiOffset][j],j+1 , (i - asciiOffset) +1);
        }
    }

    //ring 1
    for (char i = 'c'; i < 'f'; i ++)
    {
        for (int j = 2; j < 5; j++)
        {
            positions[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            //adds the button to the widget array and creates a button
            positionsW[i - asciiOffset][j].setup(i, j + 1, 0, '0', true);
            positionsW[i - asciiOffset][j].setFixedSize(50,50);
            //needed for stylesheet
            positionsW[i - asciiOffset][j].setObjectName("empty");
            connect(&positionsW[i - asciiOffset][j], SIGNAL(clicked()),this,SLOT(posClicked()));


            boardlayout->addWidget(&positionsW[i - asciiOffset][j],j +1 , (i - asciiOffset+1));
        }
    }
    //setupDialogBox();
    //thing->exec();
    connect(choices, SIGNAL(choiceMade(bool)), this, SLOT(choiceSelected(bool)));

    //clear out the middle
    positions['d' - asciiOffset][4-1].setDisp(' ');
    positions['d' - asciiOffset][4 - 1].setTerminator(true);
    positions['d' - asciiOffset][4 - 1].setValid(false);
    positionsW['d' - asciiOffset][4 - 1].setVisible(false);



    //add "lines. Has to be done manually..."
    QFrame *line[14];
    for(int i = 0; i < 14; i++)
    {
        line[i] = new QFrame();
        line[i]->setFrameShape(QFrame::HLine);
        line[i]->setStyleSheet("color: yellow");
        line[i]->setLineWidth(5);
        //line[i]->setFrameShadow(QFrame::Sunken);
    }

    boardlayout->addWidget(line[1], 0+1, 1+1);
    boardlayout->addWidget(line[2], 0+1, 2+1);
    boardlayout->addWidget(line[3], 0+1, 4+1);
    boardlayout->addWidget(line[4], 0+1, 5+1);

    boardlayout->addWidget(line[5], 6+1, 1+1);
    boardlayout->addWidget(line[6], 6+1, 2+1);
    boardlayout->addWidget(line[7], 6+1, 4+1);
    boardlayout->addWidget(line[8], 6+1, 5+1);


    boardlayout->addWidget(line[10], 1+1, 2+1);
    boardlayout->addWidget(line[11], 1+1, 4+1);

    boardlayout->addWidget(line[12], 5+1, 2+1);
    boardlayout->addWidget(line[13], 5+1, 4+1);

    QFrame *line2[14];

    for(int i = 0; i < 14; i++)
    {
        line2[i] = new QFrame();
        line2[i]->setFrameShape(QFrame::VLine);
        line2[i]->setStyleSheet("color: yellow");
        line2[i]->setLineWidth(5);
    }

    boardlayout->addWidget(line2[1], 1+1, 0+1);
    boardlayout->setAlignment(line2[1],Qt::AlignHCenter);
    boardlayout->addWidget(line2[2], 2+1, 0+1);
    boardlayout->setAlignment(line2[2],Qt::AlignHCenter);
    boardlayout->addWidget(line2[3], 4+1, 0+1);
    boardlayout->setAlignment(line2[3],Qt::AlignHCenter);
    boardlayout->addWidget(line2[4], 5+1, 0+1);
    boardlayout->setAlignment(line2[4],Qt::AlignHCenter);


    boardlayout->addWidget(line2[5], 1+1, 6+1);
    boardlayout->setAlignment(line2[5],Qt::AlignHCenter);
    boardlayout->addWidget(line2[6], 2+1, 6+1);
    boardlayout->setAlignment(line2[6],Qt::AlignHCenter);
    boardlayout->addWidget(line2[7], 4+1, 6+1);
    boardlayout->setAlignment(line2[7],Qt::AlignHCenter);
    boardlayout->addWidget(line2[8], 5+1, 6+1);
    boardlayout->setAlignment(line2[8],Qt::AlignHCenter);

    boardlayout->addWidget(line2[9], 2+1, 1+1);
    boardlayout->setAlignment(line2[9],Qt::AlignHCenter);
    boardlayout->addWidget(line2[10], 4+1, 1+1);
    boardlayout->setAlignment(line2[10],Qt::AlignHCenter);
    boardlayout->addWidget(line2[11], 2+1, 5+1);
    boardlayout->setAlignment(line2[11],Qt::AlignHCenter);
    boardlayout->addWidget(line2[12], 4+1, 5+1);
    boardlayout->setAlignment(line2[12],Qt::AlignHCenter);


    //button style sheet

    hoverStyle();



    //set up the new status layout
    QGroupBox* statusGroup1 = new QGroupBox(tr("Player 1"));
    statusGroup1->setStyleSheet("background-color: white");
    QVBoxLayout* statusBox1 = new QVBoxLayout();
    statusBox1->setStretch(0, 10);
    statusBox1->addWidget(playerPieceLabel1);
    statusBox1->addWidget(player1ActivePieceLabel);
    statusBox1->addWidget(playerMillLabel1);
    statusBox1->addWidget(player1MillLabel);
    statusBox1->addWidget(playerFlightLabel1);
    statusBox1->addWidget(player1FlightLabel);

    QGroupBox* statusGroup2 = new QGroupBox(tr("Player 2"));
    statusGroup2->setStyleSheet("background-color: white; ");
    QVBoxLayout* statusBox2 = new QVBoxLayout();
    statusBox2->setStretch(0, 10);
    statusBox2->addWidget(playerPieceLabel2 );
    statusBox2->addWidget(player2ActivePieceLabel);
    statusBox2->addWidget(playerMillLabel2);
    statusBox2->addWidget(player2MillLabel);
    statusBox2->addWidget(playerFlightLabel2);
    statusBox2->addWidget(player2FlightLabel);

    QLabel* StatsLabel = new QLabel(tr("NINE MEN'S MORRIS"));
    StatsLabel->setStyleSheet("font-weight: bold; color: white;font-size: 18px;");
    statusGroup1->setLayout(statusBox1);
    statusGroup2->setLayout(statusBox2);
    currentGamePhase->setStyleSheet("font-weight: bold; color: red;font-size: 16px;");
    currentPlayerLabel->setStyleSheet("font-weight: bold; color: orange;font-size: 16px;");
    //add to final layout
    newStatusLayout->addWidget(StatsLabel,1,0, Qt::AlignCenter);
    newStatusLayout->addWidget(statusGroup1, 2, 0, Qt::AlignCenter);
    newStatusLayout->addWidget(currentGamePhase,3,0, Qt::AlignCenter);
    newStatusLayout->addWidget(currentPlayerLabel, 4, 0, Qt::AlignCenter);
    newStatusLayout->addWidget(statusGroup2, 5, 0, Qt::AlignCenter);


    //add buttons for reset and surrender
    this->reset = new QPushButton(tr("Restart Game"));
    reset->setStyleSheet("background-color: white");
    connect(reset, SIGNAL(clicked()), SLOT(resetBoardGUI()));
    newStatusLayout->addWidget(reset, 6, 0, 1, 2);

    this->surrender = new QPushButton(tr("Surrender"));
    surrender->setStyleSheet("background-color: white");
    connect(surrender, SIGNAL(clicked()), SLOT(surrenderButtonGUI()));
    newStatusLayout->addWidget(surrender, 7, 0, 1, 2);

    QLabel * rowLabels[7];
    QLabel * colLabels[7];

    for(int i = 7; i > 0; i--) {
      rowLabels[i-1] = new QLabel(QString::number(i));
      rowLabels[i-1]->setStyleSheet("color: black; text-align: center; padding: 5px;font-size: 12px;");
      boardlayout->addWidget(rowLabels[i-1], i, 0);
    }
    for(int i = 65; i < 72; i++) {
      char ch = i;
      QString str = QString(ch);
      colLabels[i-65] = new QLabel(str);
      colLabels[i-65]->setAlignment(Qt::AlignCenter);
      colLabels[i-65]->setStyleSheet("color: black; text-align: center; padding: 5px;font-size: 12px;");
      boardlayout->addWidget(colLabels[i-65], 8, i-64);
    }







    QHBoxLayout *mainlayout = new QHBoxLayout();
    mainlayout->addLayout(newStatusLayout);
    mainlayout->addItem(spacer2);
    mainlayout->addLayout(boardlayout);
    mainlayout->addItem(spacer2);
    //mainlayout->addLayout(statusLayout);
    mainlayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainlayout);


    //    choices->exec();
    updateStatusList("----\nBoard Loaded. Begin Game \n Phase 1 Start ");


}

void BoardWidget::updateStatusList(QString inc)
{
    statusList->insertItem(0,inc);
    QString boardStatus = QString("----\n Board Status: %1  | Current Player: %2 \n "
                                  "Player 1: %3 / %4 | Mills: %5 | Flight: %6 \n "
                                  "Player 2: %7 / %8 | Mills: %9 | Flight: %10").arg(this->getState())
             .arg(this->getCurrentPlayer().getPlayerID())
            .arg(this->BoardPlayers.at(0).getPhase1Pieces())
            .arg(this->BoardPlayers.at(0).getPhase2Pieces())
            .arg(this->BoardPlayers.at(0).getStableMills())
            .arg(this->BoardPlayers.at(0).getFlight())
            .arg(this->BoardPlayers.at(1).getPhase1Pieces())
            .arg(this->BoardPlayers.at(1).getPhase2Pieces())
            .arg(this->BoardPlayers.at(1).getStableMills())
            .arg(this->BoardPlayers.at(1).getFlight());

    statusList->insertItem(0,boardStatus);
    if( BoardPlayers.at(0).getFlight() && this->state == phase2)
    {
        statusList->insertItem(0,"Flight mode active for: "+QString::number(getPlayers().at(0).getPlayerID()));
    }
    if( BoardPlayers.at(1).getFlight() && this->state == phase2)
    {
        statusList->insertItem(0,"Flight mode active for: "+QString::number(getPlayers().at(1).getPlayerID()));
    }
    player1ActivePieceLabel->setText(QString::number(BoardPlayers.at(0).getPhase2Pieces()));
    player2ActivePieceLabel->setText(QString::number(BoardPlayers.at(1).getPhase2Pieces()));

    player1MillLabel->setText(QString::number(BoardPlayers.at(0).getStableMills()));
    player2MillLabel->setText(QString::number(BoardPlayers.at(1).getStableMills()));

    player1FlightLabel->setText(BoardPlayers.at(0).getFlight() ? "On": "Off");
    player2FlightLabel->setText(BoardPlayers.at(1).getFlight() ? "On": "Off");
    currentPlayerLabel->setText("Turn: P" + QString::number(getCurrentPlayer().getPlayerID()));

    switch (state) {
    case phase1:
        currentGamePhase->setText(tr("Phase 1"));
        break;
    case phase2:
        currentGamePhase->setText(tr("Phase 2"));
        break;
    case mill:
        currentGamePhase->setText(tr("Mill"));
        break;
    case gameOver:
        currentGamePhase->setText(tr("GAME OVER"));
        currentPlayerLabel->setText("P"+ QString::number(BoardPlayers.at(getCurrentPlayer().getEnemy() -1).getPlayerID()) + " WON");
        gameoverAnnounce->setWindowTitle("Game Over!");
        gameoverAnnounce->setText("Game Over! Player "+QString::number(getCurrentPlayer().getEnemy()) + " has won! \n Press Restart Game to play again.  ");
        gameoverAnnounce->exec();
        break;
    default:
        currentGamePhase->setText(tr("NaN"));
        break;
    }



}

void BoardWidget::hoverStyle()
{
    qApp->setStyleSheet("QLabel#boldLabel { font-weight: bold; } QPushButton#empty { border: 0px; background-image: url(:/images/empty.png); } QPushButton#player1 { border: 0px; background-image: url(:/images/blue_stone.png); } QPushButton#selected { border: 0px; background-image: url(:/images/blue_stone_selected.png); } QPushButton#player2 { border: 0px; background-image: url(:/images/red_stone.png); } QPushButton#empty:hover { border: 0px; background-image: url(:/images/basic_stone_selected.png); } QPushButton#selected:hover { border: 0px; background-image: url(:/images/blue_stone.png); }");

}

void BoardWidget::selectionStyle()
{
    qApp->setStyleSheet("QLabel#boldLabel { font-weight: bold; } QPushButton#empty { border: 0px; background-image: url(:/images/empty.png); } QPushButton#player1 { border: 0px; background-image: url(:/images/blue_stone.png); } QPushButton#player2 { border: 0px; background-image: url(:/images/red_stone.png); } QPushButton#player1:hover { border: 0px; background-image: url(:/images/blue_stone_selected.png); }");

}

void BoardWidget::removeStyle()
{
    qApp->setStyleSheet("QLabel#boldLabel { font-weight: bold; } QPushButton#empty { border: 0px; background-image: url(:/images/empty.png); } QPushButton#player1 { border: 0px; background-image: url(:/images/blue_stone.png); } QPushButton#player2 { border: 0px; background-image: url(:/images/red_stone.png); } QPushButton#player2:hover { border: 0px; background-image: url(:/images/red_stone_selected.png); }");

}

void BoardWidget::gameOverButtonDisable()
{
    for (int i = 0 ;i < 7 ;i++ ) {
        for(int j = 0; j < 7; j++){
            positionsW[i][j].setEnabled(false);
        }

    }

}

void BoardWidget::AIMoveWidget()
{



    if(getCurrentPlayer().getIsAI())
    {
        QThread::msleep(500);
        switch (this->state) {
        case phase1:
        {
            string move = AIMove();
            char row = move[0];
            int column = move[1] - '0';
            positionsW[row - asciiOffset][column -1].setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
            positionsW[row - asciiOffset][column -1].setStyle(qApp->style());
            positionsW[row - asciiOffset][column -1].repaint();
            checkAndChangeState(getPlayers().at(0), getPlayers().at(1));
            displayBoard();
            if(this->state!=mill)
            {
                QString result = QString("----\n Pressed %1%2").arg(row).arg(column);
                togglePlayer();
                updateStatusList(result);
            }
            else
            {
                QString temp = QString("----\n %1 has made a mill! Select a piece to remove.").arg(getCurrentPlayer().getPlayerID());
                currentGamePhase->setText(tr("Mill Made"));
                statusList->insertItem(0,temp);
                AIMoveWidget();
            }

        }
            break;
        case phase2:
        {
            string move = AIMove();
            char row = move[0];
            int column = move[1] - '0';
            char rowGoal = move[2];
            int columnGoal = move[3] -'0';
            hoverStyle();
            positionsW[row - asciiOffset][column - 1].setObjectName("empty");
            positionsW[row - asciiOffset][column - 1].setStyle(qApp->style());
            positionsW[row - asciiOffset][column - 1].repaint();
            positionsW[rowGoal - asciiOffset][columnGoal -1].setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
            positionsW[rowGoal - asciiOffset][columnGoal -1].setStyle(qApp->style());
            positionsW[rowGoal - asciiOffset][columnGoal -1].repaint();
            checkAndChangeState(getPlayers().at(0), getPlayers().at(1));
            displayBoard();
            if(this->state!=mill)
            {
                QString result = QString("----\n Pressed %1%2").arg(row).arg(column);
                togglePlayer();
                updateStatusList(result);
            }
            else
            {
                QString temp = QString("----\n %1 has made a mill! Select a piece to remove.").arg(getCurrentPlayer().getPlayerID());
                currentGamePhase->setText(tr("Mill Made"));
                statusList->insertItem(0,temp);
                AIMoveWidget();
            }

        }
            break;
        case mill:
        {
            string move = AIMove();
            char row = move[0];
            int column = move[1] - '0';
            QString result = QString("----\n Pressed %1%2").arg(row).arg(column);
            positionsW[row - asciiOffset][column -1].setObjectName("empty");
            positionsW[row - asciiOffset][column -1].setStyle(qApp->style());
            positionsW[row - asciiOffset][column -1].repaint();
            checkAndChangeState(getPlayers().at(0), getPlayers().at(1));

            //only happens after a valid move
            togglePlayer();
            updateStatusList(result);
            displayBoard();
        }
            break;
        default:
            break;

        }
    }

}



// TODO
void BoardWidget::posClicked()
{

    //basic debugging
    QObject * obj = sender();
    BoardPositionWidget *clickedPos = qobject_cast<BoardPositionWidget*>(sender());
    char row = clickedPos->getCoord().first;
    int column = clickedPos->getCoord().second;
    QString result = QString("----\n Pressed %1%2").arg(row).arg(column);


    switch(this->state)
    {
    case phase1:
    {
        if(isValidLocation(row, column, 0, 0, this->getCurrentPlayer()))
        {
            doMovePhase1(row, column, this->getCurrentPlayer());

            clickedPos->setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
            clickedPos->setStyle(qApp->style());
            clickedPos->repaint();
            checkAndChangeState(getPlayers().at(0), getPlayers().at(1));
            //debug to console output
            displayBoard();

            if(this->state != mill)
            {    //only happens after a valid move
                togglePlayer();
                updateStatusList(result);
                AIMoveWidget();

                if(this->state == phase2)
                {
                    statusList->insertItem(0,"----\n Phase 2 Has Started!");
                    playersLeaveTheNest();
                    updateStatusList(0);

                }
                else
                {
                    break;
                }
            }
            else
            {
                QString temp = QString("----\n %1 has made a mill! Select a piece to remove.").arg(getCurrentPlayer().getPlayerID());
                currentGamePhase->setText(tr("Mill Made"));
                statusList->insertItem(0,temp);
            }
        }
        else
        {
            statusList->insertItem(0, " Invalid Location. Try again.");
        }
    }
    break;
    case phase2:
    {

        //if this variable = 1, then we're in selection.  If not, we're in drop mode. I hate GUIs.
        if(this->phase2At == 1)
        {
            if(!phase2_1Check(row, column))
            {
                statusList->insertItem(0, "Invalid selection. Select a location with your piece to move.");
                //might be wrong
                break;
            }
            else
            {
                //set internal variables
                this->rowSelected = row;
                this->columnSelected = column;
                QString currSelection = QString("----\n Selected %1%2. Select your goal position.").arg(row).arg(column);

                statusList->insertItem(0, currSelection);
                clickedPos->setObjectName("selected");
                hoverStyle();
                phase2At = 2;
                break;

            }
        }
        if(this->phase2At ==2)
        {
            //if the same position was clicked, then it should be deselected
            if(clickedPos->getCoord().first == rowSelected && clickedPos->getCoord().second == columnSelected)
            {
                clickedPos->setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
                statusList-> insertItem(0," Position deselected.");
                hoverStyle();
                clickedPos->repaint();
                phase2At = 1;
                //debugging
                displayBoard();
                break;

            }
            if(!phase2_2Check(row, column))
            {
                statusList->insertItem(0, "Invalid selection. That space is occupied.");
                //might be wrong
                break;

            }

            //if not, on to the checking of movement
            else
            {
                this->rowGoal = row;
                this->columnGoal = column;
                if(!isValidLocation(rowGoal, columnGoal, rowSelected, columnSelected,getCurrentPlayer()))
                {
                    statusList->insertItem(0, "Invalid selections. Check that you selected a spot owned by you, and that the goal is empty. Reset to Selection Stage");
                    phase2At = 1;
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].setStyle(qApp->style());
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].repaint();
                    break;



                }
                //if all is good, on to moving the piece
                else
                {
                    doMovePhase2(rowSelected, columnSelected, rowGoal, columnGoal, getCurrentPlayer());
                    phase2At = 1;
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].setObjectName("empty");
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].setStyle(qApp->style());
                    positionsW[rowSelected - asciiOffset][columnSelected - 1].repaint();
                    clickedPos->setObjectName("player"+QString::number(getCurrentPlayer().getPlayerID()));
                    clickedPos->setStyle(qApp->style());
                    clickedPos->repaint();
                    //debugging
                    displayBoard();

                    checkAndChangeState(getPlayers().at(0), getPlayers().at(1));
                    if(this->state != mill)
                    {    //only happens after a valid move
                        togglePlayer();
                        updateStatusList(result);
                        AIMoveWidget();

                    }
                    else
                    {
                        QString temp = QString("----\n %1 has made a mill! Select a piece to remove.").arg(getCurrentPlayer().getPlayerID());
                        currentGamePhase->setText(tr("Mill Made"));
                        statusList->insertItem(0,temp);
                    }
                }

            }

        }

    }
        break;
    case mill:
    {
      if(removePiece(row, column, getCurrentPlayer()))
      {
          clickedPos->setObjectName("empty");
          clickedPos->setStyle(qApp->style());
          clickedPos->repaint();
          checkAndChangeState(getPlayers().at(0), getPlayers().at(1));

          //only happens after a valid move
          togglePlayer();
          updateStatusList(result);

          //debug to console output
          displayBoard();
          AIMoveWidget();
          if(this->state == phase2)
          {
              statusList->insertItem(0,"----\n Phase 2 Has Started!");
              playersLeaveTheNest();
              updateStatusList(0);

          }
          else
          {
              break;
          }
          break;;
      }
      else
      {
          statusList->insertItem(0, " Invalid Location. Select an enemy piece. Try again.");

      }

    }
    break;
    case gameOver:
    default:
        break;

    }
    if(state == gameOver)
    {
        statusList->insertItem(0,"Game over! Player "+QString::number(getCurrentPlayer().getEnemy()) + " has won! Press Restart Game to play again. ");
        gameOverButtonDisable();
    }

}

void BoardWidget::resetBoardGUI()
{
    //rest the board
    this->resetBoard();
    //enable buttons
    for (int i = 0 ;i < 7 ;i++ ) {
        for(int j = 0; j < 7; j++){
            positionsW[i][j].setEnabled(true);
        }

    }
    //reset button states
    // ring 3
    for (char i = 'a'; i < 'h'; i+=3)
    {
        for (int j = 0; j < 7; j += 3)
        {
            positionsW[i - asciiOffset][j].setObjectName("empty");
        }
    }

    // ring 2
    for (char i = 'b'; i < 'g'; i += 2)
    {
        for (int j = 1; j < 6; j += 2)
        {
            positionsW[i - asciiOffset][j].setObjectName("empty");
        }
    }

    //ring 1
    for (char i = 'c'; i < 'f'; i ++)
    {
        for (int j = 2; j < 5; j++)
        {
            positionsW[i - asciiOffset][j].setObjectName("empty");
        }
    }

    //set style sheet
    hoverStyle();

    //clear out the middle
    positions['d' - asciiOffset][4-1].setDisp(' ');
    positions['d' - asciiOffset][4 - 1].setTerminator(true);
    positions['d' - asciiOffset][4 - 1].setValid(false);
    positionsW['d' - asciiOffset][4 - 1].setVisible(false);



    //show the decision dialog box
    choices->exec();

    //clear dialog box
    statusList->clear();
    updateStatusList("----\nBoard Reset. Begin Game \n Phase 1 Start ");



}

void BoardWidget::surrenderButtonGUI()
{
    surrenderGame();
    gameOverButtonDisable();
    statusList->insertItem(0,"You surrendered! Game Over! Player "+QString::number(getCurrentPlayer().getEnemy()) + " has won! Press Restart Game to play again.");
    updateStatusList(0);


}

void BoardWidget::choiceSelected(bool choice)
{
    BoardPlayers.at(1).setAI(choice);
}


