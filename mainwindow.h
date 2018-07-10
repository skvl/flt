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
    void loadData();
    QWidget *userNameForm();
    QWidget *selectLevel();

private:
    QToolBar* _panel;

    QVector<ExerciseData *> _data;
    QString _userName;
    QString _userSurname;
};

#endif // MAINWINDOW_H
