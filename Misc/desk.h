#ifndef DESK_H
#define DESK_H

#include "block.h"

#include <QFrame>
#include <QGridLayout>

class Desk : public QFrame
{
    Q_OBJECT
public:
    explicit Desk(QWidget *parent = nullptr);

    void clear();
    void setItems(QVector<QString> items);

private:
    void drawBorder();
    void addLayout();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent();
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    QGridLayout* _layout;

    struct Drag
    {
        Block* item;
        QPoint start;
    } _drag;
};

#endif // DESK_H
