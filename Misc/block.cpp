#include "block.h"

#include <QBoxLayout>

Block::Block(QString string, QWidget *parent) : QLabel(string, parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAlignment(Qt::AlignCenter);
}
