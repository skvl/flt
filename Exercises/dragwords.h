#ifndef DRAGWORDS_H
#define DRAGWORDS_H

#include "exercise.h"
#include "Misc/desk.h"

#include <QLabel>
#include <QFrame>
#include <QTextEdit>
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

private slots:
    void done();
    void skip();

private:
    void prepareResults();
    void prepareExercise();
    void prepareToolBar();
    void start();
    void showSentence();
    void showResults();

private:
    QToolBar* _commands;
    QLabel* _progressBar;
    QLabel* _translation;
    Desk* _sentence;
    Desk* _words;

    QLabel* _score;
    QTextEdit* _comparisons;
};

#endif // DRAGWORDS_H
