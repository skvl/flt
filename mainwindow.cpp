#include "mainwindow.h"
#include "Exercises/dragwords.h"

#include <QFrame>
#include <QInputDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , _panel(new QToolBar)
    , _data(QVector<ExerciseData *>())
{
    loadData();
    setCentralWidget(userNameForm());
}

MainWindow::~MainWindow()
{

}

void MainWindow::loadData()
{
    QDir dir("data");

    for (auto e: dir.entryInfoList())
        if (e.isDir() && !e.baseName().isEmpty())
            _data.append(new ExerciseData(e.filePath()));
}

QWidget *MainWindow::userNameForm()
{
    auto nameL = new QLabel(tr("Enter Your Name"));
    nameL->setObjectName("UserNameFormText");
    auto name = new QLineEdit("");
    auto surnameL = new QLabel(tr("Enter Your Surname"));
    surnameL->setObjectName("UserNameFormText");
    auto surname = new QLineEdit("");
    auto confirm = new QPushButton(tr("Continue"));

    connect(confirm, &QPushButton::clicked,
            [=]()
    {
        if (surname->text().isEmpty() || name->text().isEmpty())
            return;

        _userName = name->text();
        _userSurname = surname->text();

        setCentralWidget(selectLevel());
    });

    auto l = new QVBoxLayout;
    l->setSizeConstraint(QLayout::SetMinimumSize);
    l->setMargin(15);
    l->setSpacing(15);

    l->addWidget(surnameL, 0, Qt::AlignCenter);
    l->addWidget(surname, 0, Qt::AlignCenter);
    l->addWidget(nameL, 0, Qt::AlignCenter);
    l->addWidget(name, 0, Qt::AlignCenter);
    l->addWidget(confirm, 0, Qt::AlignCenter);

    auto f = new QFrame;
    f->setObjectName("UserNameFormFrame");
    f->setLayout(l);

    auto ml = new QVBoxLayout;
    ml->addWidget(f, 0, Qt::AlignCenter);

    auto w = new QWidget(this);
    w->setObjectName("UserNameForm");
    w->setLayout(ml);

    return w;
}

QWidget *MainWindow::selectLevel()
{
    auto l = new QVBoxLayout;
    l->setMargin(25);
    l->setSpacing(25);
    l->setSizeConstraint(QLayout::SetMinimumSize);

    for (auto d: _data)
    {
        auto b = new QPushButton(d->text());
        b->setMinimumSize(128, 128);
        l->addWidget(b, 0, Qt::AlignCenter);

        connect(b, &QPushButton::clicked, [=]()
        {
            d->setUserName(_userSurname, _userName);

            auto title = QString(tr("Экзамен сдаёт ")) + d->userName();
            setWindowTitle(title);

            setCentralWidget(new DragWords(d, this));
        });
    }

    auto w = new QWidget(this);
    w->setLayout(l);
    w->setObjectName("SelectLevel");

    return w;
}
