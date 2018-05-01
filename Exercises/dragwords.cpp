#include "dragwords.h"

#include <QBoxLayout>
#include <QIcon>

const QString DragWords::text = "Exercise 1";
const QString DragWords::toolTip = "Drop words to make sentence";
const QString DragWords::whatsThis = "";
const QString DragWords::icon = ":/icons/Resources/Icons/simple_drag_drop.png";

DragWords::DragWords(QWidget *parent)
    : Exercise(parent)
    , _commands(new QToolBar(this))
    , _sentence(new QFrame(this))
    , _words(new QFrame(this))
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->setMargin(10);
    layout->setSpacing(10);

    layout->addWidget(_commands, 1);
    layout->addWidget(_sentence, 3);
    layout->addWidget(_words, 1);

    prepareToolBar();

    _sentence->setFrameStyle(QFrame::Box | QFrame::Plain);
    _sentence->setMinimumSize(256, 128);

    _words->setFrameStyle(QFrame::Box | QFrame::Plain);
    _words->setMinimumSize(256, 64);
}

void DragWords::done()
{

}

void DragWords::skip()
{

}

void DragWords::prepareToolBar()
{
    _commands->setIconSize(QSize(32, 32));

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _commands->addWidget(spacer);

    QAction* doneAction = new QAction(QIcon(":/icons/Resources/Icons/done.png"),
                                            "Done", this);
    doneAction->setToolTip("Check it");
    connect(doneAction, &QAction::triggered, this, &DragWords::done);
    _commands->addAction(doneAction);

    QAction* skipAction = new QAction(QIcon(":/icons/Resources/Icons/fail.png"),
                                            "Skip", this);
    skipAction->setToolTip("Skip to next");
    connect(skipAction, &QAction::triggered, this, &DragWords::skip);
    _commands->addAction(skipAction);
}
