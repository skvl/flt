#include "mainwindow.h"
#include "Exercises/dragwords.h"
#include "Exercises/listenwords.h"

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

    QAction* dragWords = new QAction(QIcon(DragWords::icon), DragWords::text,
                                     this);
    dragWords->setToolTip(DragWords::toolTip);
    dragWords->setWhatsThis(DragWords::whatsThis);
    connect(dragWords, &QAction::triggered,
            [=](){run(new DragWords(_data, this));});
    _panel->addAction(dragWords);

    QAction* listenWords = new QAction(QIcon(ListenWords::icon),
                                       ListenWords::text,
                                       this);
    listenWords->setToolTip(ListenWords::toolTip);
    listenWords->setWhatsThis(ListenWords::whatsThis);
    connect(listenWords, &QAction::triggered,
            [=](){run(new ListenWords(_data, this));});
    _panel->addAction(listenWords);
}
