#ifndef CHOICESDIALOG_H
#define CHOICESDIALOG_H

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
#include <QLineEdit>
#include <cstdlib>
#include <ctime>
#include <random>
#include <QThread>

//! Class used to show choices before the game: Human or AI opponent, and some decision tools
class choicesdialog : public QDialog
{
    Q_OBJECT
public:
    choicesdialog(QDialog* parent = nullptr);
    void setMeUp();
private:
    //buttons to add
    //! button for human opponent
    QPushButton* twoplayerButton = new QPushButton(tr("VS Human"));
    //! button for AI opponent
    QPushButton* singleplayerButton = new QPushButton(tr("VS AI (Beta)"));
    //! generate 1 or 2
    QPushButton* flipCoinButton = new QPushButton(tr("Flip a Coin"));
    //! generate 0-100
    QPushButton* randNum = new QPushButton(tr("Random Nunber 1-100"));
    //! shows the output of the buttons
    QLineEdit* choiceDisplay = new QLineEdit();
public slots:
    void AIPressed();
    void humanPressed();
    void flipCoin();
    void randomInteger();
signals:
    void choiceMade(bool);

};

#endif // CHOICESDIALOG_H
