#ifndef DRAGWORDS_H
#define DRAGWORDS_H

#include "exercise.h"

#include <QFrame>
#include <QToolBar>

class DragWords : public Exercise
{
    Q_OBJECT
public:
    explicit DragWords(QWidget *parent = nullptr);

    QString text() const;
    QString toolTip() const;
    QString whatsThis() const;
    QIcon icon() const;

signals:
    void runnedOut(Exercise *e);

public slots:
    void run();

private slots:
    void done();
    void skip();

private:
    void prepareToolBar();

private:
    QToolBar* _commands;
    QFrame* _sentence;
    QFrame* _words;
};

#endif // DRAGWORDS_H
