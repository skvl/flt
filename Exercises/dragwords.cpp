#include "dragwords.h"

#include <QBoxLayout>
#include <QIcon>

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

QString DragWords::text() const
{
    return "Exercise 1";
}

QString DragWords::toolTip() const
{
    return "Drop words to make sentence";
}

QString DragWords::whatsThis() const
{
    return "Some longer description";
}

QIcon DragWords::icon() const
{
    return QIcon(":/icons/Resources/Icons/simple_drag_drop.png");
}

void DragWords::run()
{
    emit runnedOut(this);
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
    connect(doneAction, SIGNAL(triggered(bool)), SLOT(done()));
    _commands->addAction(doneAction);

    QAction* skipAction = new QAction(QIcon(":/icons/Resources/Icons/fail.png"),
                                            "Skip", this);
    skipAction->setToolTip("Skip to next");
    connect(skipAction, SIGNAL(triggered(bool)), SLOT(skip()));
    _commands->addAction(skipAction);
}
