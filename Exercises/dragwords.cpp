#include "dragwords.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>

const QString DragWords::text = "Drag words";
const QString DragWords::toolTip = "Drop words to make sentence";
const QString DragWords::whatsThis = "";
const QString DragWords::icon = ":/icons/Resources/Icons/simple_drag_drop.png";

DragWords::DragWords(ExerciseData &data, QWidget *parent)
    : Exercise(data, parent)
    , _commands(new QToolBar(this))
    , _translation(new QLabel(this))
    , _sentence(new Desk(this))
    , _words(new Desk(this))
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setMargin(10);
    layout->setSpacing(10);

    layout->addWidget(_commands, 1);
    layout->addWidget(_translation, 1);
    layout->addWidget(_sentence, 3);
    layout->addWidget(_words, 1);

    prepareToolBar();

    _translation->setFrameStyle(QFrame::Box | QFrame::Plain);
    _translation->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _translation->setStyleSheet("font-size: 15pt");

    _sentence->setMinimumSize(128, 64);

    start();
}

void DragWords::done()
{
    _translation->clear();
    _sentence->clear();
    _words->clear();
    _data.next();
    if ( _data.end() )
        showResults();
    else
        showSentence();
}

void DragWords::skip()
{
    _translation->clear();
    _sentence->clear();
    _words->clear();
    _data.next();
    if ( _data.end() )
        showResults();
    else
        showSentence();
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

void DragWords::start()
{
    _data.flush();
    showSentence();
}

void DragWords::showSentence()
{
    _translation->setText(_data.translation("RU"));
    _words->setItems(_data.graphemes());
}

void DragWords::showResults()
{

}
