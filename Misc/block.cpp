#include "block.h"

#include <QBoxLayout>

Block::Block(QString string, QWidget *parent) : QLabel(string, parent)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setAlignment(Qt::AlignCenter);
    setMinimumSize(64, 64);
}

Block::Block(int size, QString string, QWidget *parent)
    : Block(string, parent)
{
    _size = size;
}

QSize Block::sizeHint() const
{
    return QSize(_size, _size);
}
