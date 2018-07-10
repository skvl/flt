#ifndef DRAGWORDS_H
#define DRAGWORDS_H

#include "exercise.h"
#include "Misc/desk.h"

#include <QLabel>
#include <QLCDNumber>
#include <QFrame>
#include <QTextEdit>
#include <QTime>
#include <QTimer>
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
    explicit DragWords(ExerciseData& data, QWidget *parent = nullptr);

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void done();
    void play();
    void restart();
    void show();
    void skip();
    void timer();

private:
    void flush();
    void load();
    void prepareResults();
    void prepareExercise();
    void prepareToolBar();
    void start();
    void showResults();

private:
    QToolBar* _commands;
    QLCDNumber* _progressBar;
    QLabel* _translation;
    Desk* _sentence;
    Desk* _words;

    QLabel* _score;
    QTextEdit* _comparisons;

    QTime _startAt;
    QTimer* _timer;
    QLCDNumber* _stopwatch;
};

#endif // DRAGWORDS_H
