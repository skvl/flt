#include "dragwords.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>
#include <QScrollArea>

const QString DragWords::text = "Drag words";
const QString DragWords::toolTip = "Drop words to make sentence";
const QString DragWords::whatsThis = "";
const QString DragWords::icon = ":/icons/Resources/Icons/simple_drag_drop.png";

DragWords::DragWords(ExerciseData &data, QWidget *parent)
    : Exercise(data, parent)
    , _commands(new QToolBar(this))
    , _progressBar(new QLabel(this))
    , _comparisons(new QTextEdit(this))
    , _translation(new QLabel(this))
    , _sentence(new Desk(this))
    , _words(new Desk(this))
{
    prepareExercise();
    prepareResults();
}

void DragWords::done()
{
    _data.addAnswer(_sentence->items());
    skip();
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

void DragWords::prepareResults()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, _results);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setMargin(10);
    layout->setSpacing(10);

    _score = new QLabel();
    layout->addWidget(_score);
    _score->setFrameStyle(QFrame::Box | QFrame::Plain);
    _score->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _score->setStyleSheet("font-size: 15pt");

    layout->addWidget(_comparisons);
}

void DragWords::prepareExercise()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, _exercise);
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

void DragWords::prepareToolBar()
{
    _commands->setIconSize(QSize(32, 32));

    _progressBar->setFrameStyle(QFrame::Box | QFrame::Plain);
    _progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _progressBar->setStyleSheet("font-size: 15pt");
    _commands->addWidget(_progressBar);

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
    _progressBar->setText(QString::number(_data.index()));
    _translation->setText(_data.translation("RU"));
    _words->setItems(_data.graphemes());
}

void DragWords::showResults()
{
    _data.startCheck();

    QString results = "<html><body>";

    for (auto i = 0; !_data.end(); ++i, _data.next())
    {
        results += QString("<p>") + QString::number(i) + QString(". ");
        results += QString("Правильный ответ: <font size=\"12\">") + _data.correctSentence() + "</p>";
        results += "<p>Ответ пользователя: ";
        if (_data.compare())
            results += QString("<font color=green size=\"14\">");
        else
            results += QString("<font color=red size=\"14\">");
        results += _data.userAnswer() + "</font></p>\n\n";
    }
    results += "</body></html>";
    _comparisons->setText(results);
    _comparisons->setStyleSheet("font-size:15pt;");

    auto score = QString::number(int(_data.score() * 5));
    score += QString(" (Правильно ") +
            QString::number(_data.correctAnswers()) +
            QString(" из ") +
            QString::number(_data.count()) +
            QString(")");
    _score->setText(score);
    _pages->setCurrentWidget(_results);
}
