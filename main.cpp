#include "mainwindow.h"
#include <QApplication>

/*
 * TODO #1 Добавить обработку ошибок соединений.
 *
 * Если `QObject::connect() = false`, то необходимо вывести предупреждение об
 * ошибке и прервать выполнение.
 * Данную возможность стоит вынести в класс.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
