#include "block.h"

#include <QBoxLayout>

Block::Block(QString string, QWidget *parent) : QLabel(string, parent)
{
    // qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 blue, stop: 0.8 white, stop: 1 blue)
    setStyleSheet("Block{background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 white, stop: 0.1 blue, stop: 1 white);"
                  "border-width:1px;"
                  "border-color :rgb(0,0,0);"
                  "border-radius:10px;"
                  "border-style:solid;"
                  "color:white;"
                  "font-size:30pt;}");

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
