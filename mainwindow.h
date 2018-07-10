#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Exercises/exercise.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void prepareToolBar();
    QWidget *userNameForm();

private:
    QToolBar* _panel;

    ExerciseData _data;
};

#endif // MAINWINDOW_H
