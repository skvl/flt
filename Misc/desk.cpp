#include "desk.h"

#include <QBitmap>
#include <QPainter>

Desk::Desk(QWidget *parent)
    : QFrame(parent)
    , _layout(new QGridLayout(this))
    , _items(QVector<QLabel*>())
{
    drawBorder();
    addLayout();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void Desk::setItems(QVector<QString> items)
{
    clear();

    int column = 0;
    for (auto word: items)
    {
        QLabel* label = new QLabel(word);

        label->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        label->setStyleSheet("font-size: 30pt");
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        _layout->addWidget(label, 0, column++);
        _items.push_back(label);
    }
}

void Desk::drawBorder()
{
    setStyleSheet("Desk{background-color:rgb(255,255,255);"
                  "border-width:1px;"
                  "border-color :rgb(0,0,0);"
                  "border-radius:10px;"
                  "border-style:solid;}");
}

/*
 * TODO Создать собственный Layout
 *
 * Собственный Layout мог бы отслеживать изменения размеров родительского
 * QWidget и рассчитывать количество столбцов, строк, размеры пустых областей.
 *
 * Источники:
 * - Flow Layout Example
 */
void Desk::addLayout()
{
    _layout->setSizeConstraint(QLayout::SetMinimumSize);
    _layout->setMargin(15);
    _layout->setSpacing(15);
}

void Desk::clear()
{
    for (auto old: _items)
    {
        _layout->removeWidget(old);
        delete old;
    }

    _items.clear();
}
