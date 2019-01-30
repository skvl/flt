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
#include <QtMath>

#include <QDebug>

const int Desk::_spacing = 10;

Desk::Desk(QWidget *parent)
    : QFrame(parent)
    , _layout(new QGridLayout(this))
{
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

    int _columns = items.size();

    // TODO Добавить статическую функцию `Block::minimalSize`
    const int minSide = 64;
    int side = minSide;

    const int margins = 2 * _spacing;
    for (int rows = 1; rows <= items.size(); ++rows)
    {
        int columns = qCeil(float(items.size()) / rows);

        const int vSpaces = (rows - 1) * _spacing;
        const int h = std::max((height() - margins - vSpaces) / rows, minSide);

        const int hSpaces = (columns - 1) * _spacing;
        const int w = std::max((width() - margins - hSpaces) / columns, minSide);

        const int s = std::min(w, h);
        if (s > side)
        {
            side = s;
            _columns = columns;
        }
    }

    int column = 0;
    int row = 0;
    for (auto word: items)
    {
        Block* label = new Block(side, word);

        _layout->addWidget(label, row, column);

        if (++column >= _columns)
        {
            column = 0;
            ++row;
        }
    }
}

QVector<QString> Desk::items() const
{
    QVector<QString> result = QVector<QString>();

    for (auto i = 0; i < _layout->count(); ++i)
    {
        QLayoutItem* item = _layout->itemAt(i);
        auto block = static_cast<Block*>(item->widget());
        if (block)
            result.push_back(block->text());
        else
            qDebug() << "Warning! Layout item without widget.";
    }

    return result;
}

void Desk::resizeSlot()
{
    setItems(items());
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
    _layout->setMargin(_spacing);
    _layout->setSpacing(_spacing);
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

void Desk::dragMoveEvent(QDragMoveEvent *)
{
}

void Desk::dropEvent(QDropEvent *event)
{
    auto i = items();
    i.append(event->mimeData()->text());
    setItems(i);

    event->acceptProposedAction();
}
