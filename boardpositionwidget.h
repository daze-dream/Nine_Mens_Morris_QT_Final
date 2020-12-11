#ifndef BOARDPOSITIONWIDGET_H
#define BOARDPOSITIONWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QSignalMapper>

#include "BoardPosition.h"
//! GUI representation of a board location. Uses clicked() SLOT
class BoardPositionWidget: public QPushButton, public BoardPosition
{
    Q_OBJECT
public:
    //! constructor. Nothing needed really.
    BoardPositionWidget(QPushButton *parent = nullptr);

};

#endif // BOARDPOSITIONWIDGET_H
