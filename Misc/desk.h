#ifndef DESK_H
#define DESK_H

#include <QFrame>
#include <QGridLayout>
#include <QLabel>

class Desk : public QFrame
{
    Q_OBJECT
public:
    explicit Desk(QWidget *parent = nullptr);

    void setItems(QVector<QString> items);

private:
    void drawBorder();
    void addLayout();
    void clear();

private:
    QGridLayout* _layout;
    QVector<QLabel*> _items;
};

#endif // DESK_H
