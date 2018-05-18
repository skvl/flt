#include "listenwords.h"

#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QIcon>
#include <QScrollArea>
#include <QSound>

#include <QMediaPlayer>

const QString ListenWords::text = "Listen words";
const QString ListenWords::toolTip = "Listen and drag words to make sentence";
const QString ListenWords::whatsThis = "";
const QString ListenWords::icon = ":/icons/Resources/Icons/simple_listen.png";

ListenWords::ListenWords(ExerciseData &data, QWidget *parent)
    : Exercise(data, parent)
    , _commands(new QToolBar(this))
    , _progressBar(new QLabel(this))
    , _comparisons(new QTextEdit(this))
    , _sentence(new Desk(this))
    , _words(new Desk(this))
{
    prepareExercise();
    prepareResults();
}

void ListenWords::done()
{
    _data.addAnswer(_sentence->items());
    skip();
}

void ListenWords::play()
{
    if (_data.audio().isEmpty())
    {
        QString message =
                QString("This sentence does not have associatedd audio.\n\n") +
                QString("You should compose this one:\n") +
                _data.translation("RU");

        auto dialog =
                new QMessageBox(QMessageBox::Warning,
                                "Exercise interruption",
                                message,
                                QMessageBox::Ok);
        dialog->exec();
    }
    else
    {
        // TODO Узнать по какой причине не работает
        // QSound::play(_data.audio());

        auto player = new QMediaPlayer;
        player->setMedia(QUrl(_data.audio()));
        player->setVolume(100);
        player->play();

        // TODO Узнать как освобождать память
        // delete player;
    }
}

void ListenWords::skip()
{
    _sentence->clear();
    _words->clear();
    _data.next();
    if ( _data.end() )
        showResults();
    else
        showSentence();
}

void ListenWords::prepareResults()
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

void ListenWords::prepareExercise()
{
    QBoxLayout* layout = new QBoxLayout(QBoxLayout::TopToBottom, _exercise);
    layout->setSizeConstraint(QLayout::SetMinimumSize);
    layout->setMargin(10);
    layout->setSpacing(10);

    layout->addWidget(_commands, 1);
    layout->addWidget(_sentence, 3);
    layout->addWidget(_words, 1);

    prepareToolBar();

    _sentence->setMinimumSize(128, 64);

    start();
}

void ListenWords::prepareToolBar()
{
    _commands->setIconSize(QSize(32, 32));

    _progressBar->setFrameStyle(QFrame::Box | QFrame::Plain);
    _progressBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    _progressBar->setStyleSheet("font-size: 15pt");
    _commands->addWidget(_progressBar);

    QWidget* spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _commands->addWidget(spacer);

    QAction* playAction = new QAction(QIcon(":/icons/Resources/Icons/play.png"),
                                            "Play", this);
    playAction->setToolTip("Play it");
    connect(playAction, &QAction::triggered, this, &ListenWords::play);
    _commands->addAction(playAction);

    QAction* doneAction = new QAction(QIcon(":/icons/Resources/Icons/done.png"),
                                            "Done", this);
    doneAction->setToolTip("Check it");
    connect(doneAction, &QAction::triggered, this, &ListenWords::done);
    _commands->addAction(doneAction);

    QAction* skipAction = new QAction(QIcon(":/icons/Resources/Icons/fail.png"),
                                            "Skip", this);
    skipAction->setToolTip("Skip to next");
    connect(skipAction, &QAction::triggered, this, &ListenWords::skip);
    _commands->addAction(skipAction);
}

void ListenWords::start()
{
    _data.flush();
    showSentence();
}

void ListenWords::showSentence()
{
    _progressBar->setText(QString::number(_data.index()));
    _words->setItems(_data.graphemes());
}

void ListenWords::showResults()
{
    _data.startCheck();

    QString results = "<html><body>";

    for (; !_data.end(); _data.next())
    {
        results += QString("<p>Original: <font size=\"12\">") + _data.correctSentence() + "<p>";
        results += "<p>User answer: ";
        if (_data.compare())
            results += QString("<font color=green size=\"14\">");
        else
            results += QString("<font color=red size=\"14\">");
        results += _data.userAnswer() + "</font></p>\n\n";
    }
    results += "</body></html>";
    _comparisons->setText(results);
    _comparisons->setStyleSheet("font-size:15pt;");

    _score->setText(QString::number(int(_data.score() * 5)));
    _pages->setCurrentWidget(_results);
}