#ifndef BLOCK_H
#define BLOCK_H

#include <QLabel>

class Block : public QLabel
{
    Q_OBJECT
public:
    explicit Block(QString string, QWidget *parent = nullptr);
};

#endif // BLOCK_H
