#include "choicesdialog.h"

choicesdialog::choicesdialog(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle("Game Setup...");

    connect(twoplayerButton, SIGNAL(clicked()), this, SLOT(humanPressed()));
    connect(singleplayerButton, SIGNAL(clicked()), this, SLOT(AIPressed()));
    connect(flipCoinButton, SIGNAL(clicked()), this, SLOT(flipCoin()));
    connect(randNum, SIGNAL(clicked()), this, SLOT(randomInteger()));

    //main layout
    QGridLayout* choicesLayout = new QGridLayout();

    //opponent selection sublayout
    QGroupBox *opponentSelect = new QGroupBox(tr("Select An Opponent: "));
    QVBoxLayout *opponentSelectLayout = new QVBoxLayout;
    opponentSelectLayout->addWidget(twoplayerButton);
    opponentSelectLayout->addWidget(singleplayerButton);
    opponentSelect->setLayout(opponentSelectLayout);
    //tool layout
    QGroupBox *toolBox = new QGroupBox(tr("Tools to help play"));
    QVBoxLayout *toolBoxLayout = new QVBoxLayout;
    toolBoxLayout->addWidget(flipCoinButton);
    toolBoxLayout->addWidget(randNum);
    choiceDisplay->setReadOnly(true);
    toolBoxLayout->addWidget(choiceDisplay);
    toolBox->setLayout(toolBoxLayout);
    //set final layout
    choicesLayout->addWidget(opponentSelect, 0,0);
    choicesLayout->addWidget(toolBox, 0,1);
    this->setLayout(choicesLayout);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

}
//slots
void choicesdialog::AIPressed()
{
    emit choiceMade(true);
    this->close();
}

void choicesdialog::humanPressed()
{
    emit choiceMade(false);
    this->close();
}

void choicesdialog::flipCoin()
{
    choiceDisplay->clear();
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(1, 2);
    choiceDisplay->insert("Flipped...");

    //choiceDisplay->clear();

    int x  = dist(thing);
    QThread::msleep(500);
    if(x == 1)
    {

        choiceDisplay->insert(" Heads");
    }
    else
    {

        choiceDisplay->insert(" Tails");
    }

}

void choicesdialog::randomInteger()
{
    choiceDisplay->clear();
    std::random_device rd;
    std::mt19937 thing(rd());
    std::uniform_int_distribution<int> dist(0, 100);
    int x  = dist(thing);
    choiceDisplay->insert("Got ");
    choiceDisplay->insert(QString::number(x));

}
