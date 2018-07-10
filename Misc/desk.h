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
    QVector<QString> items() const;

public slots:
    // TODO Попробовать применить `resizeEvent()`
    void resizeSlot();

private:
    void addLayout();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent();
    void dragMoveEvent(QDragMoveEvent *);
    void dropEvent(QDropEvent *event);

private:
    static const int _spacing;
    QGridLayout* _layout;

    struct Drag
    {
        Block* item;
        QPoint start;
    } _drag;
};

#endif // DESK_H
