#ifndef EXERCISE_H
#define EXERCISE_H

#include "exercisedata.h"

#include <QStackedLayout>
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
    explicit Exercise(ExerciseData* data, QWidget *parent = nullptr)
        : QWidget(parent)
        , _data(data)
        , _pages(new QStackedLayout(this))
        , _exercise(new QWidget())
        , _results(new QWidget())
    {
        Q_ASSERT(_exercise != nullptr);
        Q_ASSERT(_results != nullptr);

        _pages->addWidget(_exercise);
        _pages->addWidget(_results);

        _pages->setCurrentWidget(_exercise);
    }

protected:
    ExerciseData* _data;
    QStackedLayout* _pages;
    QWidget* _exercise;
    QWidget* _results;
};

#endif // EXERCISE_H
