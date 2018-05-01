#ifndef EXERCISE_H
#define EXERCISE_H

#include <QWidget>

class Exercise : public QWidget
{
    Q_OBJECT
public:
    explicit Exercise(QWidget *parent = nullptr) : QWidget(parent) {}

    virtual QString text() const = 0;
    virtual QString toolTip() const = 0;
    virtual QString whatsThis() const = 0;
    virtual QIcon icon() const = 0;

signals:
    virtual void runnedOut(Exercise *e);

public slots:
    virtual void run() = 0;
};

#endif // EXERCISE_H
