#include "desk.h"

#include <QApplication>
#include <QBitmap>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMoveEvent>
#include <QMouseEvent>
#include <QPainter>

#include <QDebug>

Desk::Desk(QWidget *parent)
    : QFrame(parent)
    , _layout(new QGridLayout(this))
{
    drawBorder();
    addLayout();

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAcceptDrops(true);
}

void Desk::clear()
{
    QLayoutItem* oldItem = nullptr;
    while ( (oldItem = _layout->takeAt(0)) )
    {
        auto oldWidget = oldItem->widget();
        if (oldWidget)
        {
            _layout->removeWidget(oldWidget);
            delete oldWidget;
        }
        else
            qDebug() << "Warning! Layout item without widget.";
    }
}

void Desk::setItems(QVector<QString> items)
{
    clear();

    int column = 0;
    for (auto word: items)
    {
        Block* label = new Block(word);

        _layout->addWidget(label, 0, column++);
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

void Desk::mousePressEvent(QMouseEvent *event)
{
    _drag.item = dynamic_cast<Block*>(this->childAt(event->pos()));
    if (_drag.item)
        _drag.start = event->globalPos();
}

void Desk::mouseMoveEvent(QMouseEvent *event)
{
    if (_drag.item)
    {
        int distance = (event->globalPos() - _drag.start).manhattanLength();
        if (distance > QApplication::startDragDistance())
        {
            QMimeData* mime = new QMimeData;
            mime->setText(_drag.item->text());

            QDrag* drag = new QDrag(this);
            drag->setMimeData(mime);
            if (Qt::MoveAction == drag->exec())
            {
                _layout->removeWidget(_drag.item);
                delete _drag.item;
                _drag.item = nullptr;
            }
        }
    }
}

void Desk::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->source() != this && event->mimeData()->hasFormat("text/plain"))
        event->acceptProposedAction();
}

void Desk::dragLeaveEvent()
{
}

void Desk::dragMoveEvent(QDragMoveEvent *event)
{
}

void Desk::dropEvent(QDropEvent *event)
{
    Block* label = new Block(event->mimeData()->text());
    _layout->addWidget(label, 0, _layout->count());
    event->acceptProposedAction();
}
