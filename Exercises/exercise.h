#ifndef EXERCISE_H
#define EXERCISE_H

#include <QWidget>

class Exercise : public QWidget
{
    Q_OBJECT

public:
    static const QString text;
    static const QString toolTip;
    static const QString whatsThis;
    static const QString icon;

public:
    explicit Exercise(QWidget *parent = nullptr) : QWidget(parent) {}
};

#endif // EXERCISE_H
