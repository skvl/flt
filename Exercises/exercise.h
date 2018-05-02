#ifndef EXERCISE_H
#define EXERCISE_H

#include "exercisedata.h"

#include <QWidget>

class Exercise : public QWidget
{
    Q_OBJECT

public:
    static const QString text;
    static const QString toolTip;
    static const QString whatsThis;
    static const QString icon;

protected:
    explicit Exercise(ExerciseData& data, QWidget *parent = nullptr)
        : QWidget(parent)
        , _data(data)
    {}

protected:
    ExerciseData& _data;
};

#endif // EXERCISE_H
