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
    , _sentence(new QFrame(this))
    , _words(new QFrame(this))
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

    _sentence->setFrameStyle(QFrame::Box | QFrame::Plain);
    _sentence->setMinimumSize(256, 128);

    _words->setFrameStyle(QFrame::Box | QFrame::Plain);
    _words->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QGridLayout* wordsLayout = new QGridLayout(_words);
    wordsLayout->setSizeConstraint(QLayout::SetMinimumSize);
    wordsLayout->setMargin(5);
    wordsLayout->setSpacing(5);

    start();
}

void DragWords::done()
{
    _data.next();
    if ( _data.end() )
        showResults();
    else
        showSentence();
}

void DragWords::skip()
{
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
    auto wordsLayout = static_cast<QGridLayout*>(_words->layout());

    QLayoutItem* old = nullptr;
    while ((old = wordsLayout->takeAt(0)) != 0)
    {
        auto oldWidget = old->widget();
        if (oldWidget)
            delete oldWidget;
    }

    _translation->setText(_data.translation("RU"));

    int row = 0;
    int column = 0;
    for (auto word: _data.graphemes())
    {
        QLabel* label = new QLabel(word);

        label->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        label->setStyleSheet("font-size: 30pt");
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        wordsLayout->addWidget(label, row, column++);
    }
}

void DragWords::showResults()
{

}
