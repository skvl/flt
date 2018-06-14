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
    , _progressBar(new QLCDNumber(4, this))
    , _comparisons(new QTextEdit(this))
    , _translation(new QLabel(this))
    , _sentence(new Desk(this))
    , _words(new Desk(this))
    , _startAt(QTime(0, 0, 0, 0))
    , _timer(new QTimer(this))
    , _stopwatch(new QLCDNumber(8, this))
{
    prepareExercise();
    prepareResults();

    connect(_timer, SIGNAL(timeout()), SLOT(timer()));
    _timer->start(1000);
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

void DragWords::timer()
{
    _startAt = _startAt.addSecs(1);
    auto current = _startAt.toString("hh:mm:ss");
    if ((_startAt.second() % 2) == 0)
        current.replace(':', ' ');
    _stopwatch->display(current);
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
    _score->setLineWidth(2);
    _score->setContentsMargins(0, 0, 0, 2);
    _score->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _score->setStyleSheet("font-size: 24pt; color: #eeeeec");

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
    _translation->setLineWidth(2);
    _translation->setContentsMargins(0, 0, 0, 2);
    _translation->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _translation->setStyleSheet("font-size: 24pt; color: #eeeeec");

    _sentence->setMinimumSize(128, 64);

    start();
}

void DragWords::prepareToolBar()
{

    _commands->setIconSize(QSize(64, 64));

    _progressBar->setFrameStyle(QFrame::Box | QFrame::Plain);
    _progressBar->setLineWidth(2);
    _progressBar->setContentsMargins(0, 0, 0, 2);
    _progressBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _progressBar->setMinimumSize(96, 64);
    _progressBar->setStyleSheet("color: #eeeeec");
    _progressBar->setSegmentStyle(QLCDNumber::Flat);
    _commands->addWidget(_progressBar);

    auto separator = new QWidget(this);
    separator->setMinimumSize(64, 64);
    _commands->addWidget(separator);

    _stopwatch->setFrameStyle(QFrame::Box | QFrame::Plain);
    _stopwatch->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _stopwatch->setLineWidth(2);
    _stopwatch->setContentsMargins(0, 0, 0, 2);
    _stopwatch->setMinimumSize(192, 64);
    _stopwatch->setSegmentStyle(QLCDNumber::Flat);
    _stopwatch->setStyleSheet("color: #eeeeec");
    _commands->addWidget(_stopwatch);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _commands->addWidget(spacer);

    QAction* doneAction = new QAction(QIcon(":/icons/Resources/Icons/done.png"),
                                            "Done", this);
    doneAction->setToolTip("Check it");
    connect(doneAction, &QAction::triggered, this, &DragWords::done);
    _commands->addAction(doneAction);

    separator = new QWidget(this);
    separator->setMinimumSize(64, 64);
    _commands->addWidget(separator);

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
    _progressBar->display(_data.index());
    _translation->setText(_data.translation("RU"));
    _words->setItems(_data.graphemes());
}

void DragWords::showResults()
{
    auto resultTime = _startAt.toString("hh:mm:ss");

    _data.startCheck();

    auto score = QString::number(int(_data.score() * 5));
    score += QString(" (Правильно ") +
            QString::number(_data.correctAnswers()) +
            QString(" из ") +
            QString::number(_data.count()) +
            QString(")");
    _score->setText(score);

    QString results = "<html><body>";
    results += QString("<p>Экзаменуемый: ") + _data.userName() + QString("</p>");
    results += QString("<p>Время экзамена: ") + resultTime + QString("</p>\n\n");
    results += QString("<p>Оценка: ") + score + QString("</p>\n\n");

    for (auto i = 1; !_data.end(); ++i, _data.next())
    {
        results += QString("<p>") + QString::number(i) + QString(". ");
        results += QString("Правильный ответ: <font size=\"12\">") + _data.correctSentence() + "</p>";
        results += "<p>Ответ пользователя (";
        if (_data.compare())
            results += QString("правильный): <font color=#859900 size=\"14\">");
        else
            results += QString("неправильный): <font color=#dc322f size=\"14\">");
        results += _data.userAnswer() + "</font></p>\n\n";
    }
    results += "</body></html>";
    _comparisons->setText(results);
    _comparisons->setStyleSheet("font-size:15pt;");

    _pages->setCurrentWidget(_results);
}
