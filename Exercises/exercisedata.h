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

    int index() const;
    int count() const;
    QString audio() const;
    QVector<QString> graphemes() const;
    QString translation(QString language) const;

    void addAnswer(QVector<QString> userAnswer);
    QString correctSentence() const;
    QString userAnswer() const;
    bool compare() const;
    unsigned correctAnswers() const;
    float score() const;

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
