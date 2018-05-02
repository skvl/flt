#ifndef EXERCISEDATA_H
#define EXERCISEDATA_H


#include <QMap>
#include <QtXml>

// TODO Добавить обработку ошибок (QMessageBox)
class ExerciseData
{
public:
    ExerciseData();

    void flush();
    void next();
    bool end();

    QString audio() const;
    QVector<QString> graphemes() const;
    QString translation(QString language) const;

private:
    void parser(const QDomNode &node);

private:
    struct Sentence
    {
        QString audio;
        QVector<QString> graphemes;
        QMap<QString, QString> translations;
    };

    QVector<Sentence> _data;
    QVector<Sentence>::iterator _iterator;
};

#endif // EXERCISEDATA_H
