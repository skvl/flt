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

public slots:
    void run(Exercise *e);

private:
    void prepareToolBar();

private:
    QToolBar* _panel;
};

#endif // MAINWINDOW_H
