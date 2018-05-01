#include "mainwindow.h"
#include "Exercises/dragwords.h"

#include <QToolBar>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _panel(new QToolBar)
{
    prepareToolBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::run(Exercise *e)
{
    setCentralWidget(e);
}

// TODO Добавить перечисление классов упражнений
void MainWindow::prepareToolBar()
{
    addToolBar(Qt::LeftToolBarArea, _panel);
    _panel->setIconSize(QSize(64, 64));

    Exercise* e = new DragWords(this);
    connect(e, SIGNAL(runnedOut(Exercise*)), SLOT(run(Exercise*)));
    QAction* action = new QAction(e->icon(), e->text(), this);
    action->setToolTip(e->toolTip());
    action->setWhatsThis(e->whatsThis());
    connect(action, SIGNAL(triggered(bool)), e, SLOT(run()));
    _panel->addAction(action);
}
