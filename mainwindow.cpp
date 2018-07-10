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
    , _data(ExerciseData())
{
    setCentralWidget(userNameForm());
}

MainWindow::~MainWindow()
{

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

        _data.setUserName(surname->text(), name->text());

        auto title = QString(tr("Экзамен сдаёт ")) + _data.userName();
        setWindowTitle(title);

        setCentralWidget(new DragWords(_data, this));
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
