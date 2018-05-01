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

    QAction* action = new QAction(QIcon(DragWords::icon), DragWords::text,
                                  this);
    action->setToolTip(DragWords::toolTip);
    action->setWhatsThis(DragWords::whatsThis);
    connect(action, &QAction::triggered, [=](){run(new DragWords(this));});
    _panel->addAction(action);
}
