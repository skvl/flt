#ifndef EXERCISEDATA_H
#define EXERCISEDATA_H


#include <QMap>
#include <QtXml>

// TODO Добавить обработку ошибок (QMessageBox)
class ExerciseData
{
public:
    using CheckResult = QMap<QVector<QString>, QPair<QVector<QString>, bool>>;

public:
    ExerciseData();

    void flush();
    void next();
    bool end();

    QString audio() const;
    QVector<QString> graphemes() const;
    QString translation(QString language) const;

    void addAnswer(QVector<QString> answer);
    QVector<QString> answer() const;
    bool compare() const;

    void startCheck();

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

    struct Answer
    {
        QVector<QString> graphemes;
    };

    QVector<Answer> _answers;
};

#endif // EXERCISEDATA_H
