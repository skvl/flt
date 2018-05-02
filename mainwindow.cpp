#include "mainwindow.h"
#include "Exercises/dragwords.h"

#include <QMessageBox>
#include <QToolBar>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _panel(new QToolBar)
    , _data(ExerciseData())
{
    prepareToolBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::run(Exercise *e)
{
    auto current = centralWidget();

    if (current)
    {
        auto dialog =
                new QMessageBox(QMessageBox::Warning,
                                "Exercise interruption",
                                "You are going to interrupt the exercise."
                                "All changes will be lost.\n\n"
                                "Do You agree?",
                                QMessageBox::Yes | QMessageBox::No);

        if (QMessageBox::Yes == dialog->exec())
        {
            delete current;
            setCentralWidget(e);
        }
    }
    else
        setCentralWidget(e);
}

// TODO Добавить перечисление классов упражнений
void MainWindow::prepareToolBar()
{
    addToolBar(Qt::LeftToolBarArea, _panel);
    _panel->setIconSize(QSize(64, 64));

    QAction* action = new QAction(QIcon(DragWords::icon), DragWords::text,
                                  this);
    action->setToolTip(DragWords::toolTip);
    action->setWhatsThis(DragWords::whatsThis);
    connect(action, &QAction::triggered,
            [=](){run(new DragWords(_data, this));});
    _panel->addAction(action);
}
