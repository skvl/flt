#ifndef DRAGWORDS_H
#define DRAGWORDS_H

#include "exercise.h"

#include <QFrame>
#include <QToolBar>

class DragWords : public Exercise
{
    Q_OBJECT

public:
    static const QString text;
    static const QString toolTip;
    static const QString whatsThis;
    static const QString icon;

public:
    explicit DragWords(QWidget *parent = nullptr);

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
