#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>

class Block : public QLabel
{
    Q_OBJECT
public:
    explicit Block(QString string, QWidget *parent = nullptr);
    explicit Block(int size, QString string, QWidget *parent = nullptr);

    QSize sizeHint() const;

private:
    int _size;
};

#endif // BLOCK_H
