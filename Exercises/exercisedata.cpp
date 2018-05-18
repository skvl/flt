#include "exercisedata.h"

#include <QRandomGenerator>

#include <QDebug>

ExerciseData::ExerciseData()
    : _data(QVector<Sentence>())
    , _iterator(_data.begin())
    , _answers(QVector<Answer>())
{
    QDomDocument doc;
    QFile file("HSK/HSK-I/sentences.xml");

    if (file.open(QIODevice::ReadOnly))
    {
        auto errorMessage = QString("");
        int errorLine = 0;
        int errorColumn = 0;

        if (doc.setContent(&file, &errorMessage, &errorLine, &errorColumn))
        {
            parser(doc.documentElement());
        }
        else
            qDebug() << errorMessage << errorLine << errorColumn;
    }
    else
        qDebug() << "Failed to open file";

    flush();
}

void ExerciseData::flush()
{
    _iterator = _data.begin();

    for (auto i = 0; i < _data.count(); ++i)
        _answers.push_back(Answer());
}

void ExerciseData::next()
{
    if (_iterator < _data.end())
        _iterator++;
}

bool ExerciseData::end()
{
    if (_iterator == _data.end())
        return true;
    else
        return false;
}

int ExerciseData::index() const
{
    return _iterator - _data.begin() + 1;
}

int ExerciseData::count() const
{
    return _data.count();
}

QString ExerciseData::audio() const
{
    Q_ASSERT(_iterator < _data.end());
    return (*_iterator).audio;
}

QVector<QString> ExerciseData::graphemes() const
{
    Q_ASSERT(_iterator < _data.end());

    QVector<QString> initial = (*_iterator).graphemes;
    QVector<QString> result = QVector<QString>();

    int count = 0;
    while ((count = initial.count()) > 0)
    {
        auto idx = QRandomGenerator::global()->bounded(count);
        result.push_back(initial.takeAt(idx));
    }

    return result;
}

QString ExerciseData::translation(QString language) const
{
    Q_ASSERT(_iterator < _data.end());

    QMap<QString, QString> translations = (*_iterator).translations;

    if (translations.contains(language))
        return translations[language];
    else
        return "";
}

void ExerciseData::addAnswer(QVector<QString> answer)
{
    _answers[_iterator - _data.begin()].graphemes = answer;
}

QString ExerciseData::correctSentence() const
{
    Q_ASSERT(_iterator < _data.end());

    QString result = QString();
    for (auto w: (*_iterator).graphemes)
        result.append(w + "");

    return result;
}

QString ExerciseData::userAnswer() const
{
    Q_ASSERT(_iterator < _data.end());

    QString result = QString();
    for (auto w: _answers[_iterator - _data.begin()].graphemes)
        result.append(w + "");

    return result;
}

bool ExerciseData::compare() const
{
    Q_ASSERT(_iterator < _data.end());
    return _answers[_iterator - _data.begin()].graphemes ==
            (*_iterator).graphemes;
}

unsigned ExerciseData::correctAnswers() const
{
    unsigned num = 0;
    for (auto i = 0; i < count(); ++i)
        if (_answers[i].graphemes == _data[i].graphemes)
            ++num;

    return num;
}

float ExerciseData::score() const
{
    return correctAnswers() / count();
}

void ExerciseData::startCheck()
{
    _iterator = _data.begin();
}

void ExerciseData::parser(const QDomNode &node)
{
    QDomNode current = node.firstChild();

    while ( !current.isNull() )
    {
        if ( current.isElement() )
        {
            QDomElement e = current.toElement();

            if ( !e.isNull() )
            {
                if (e.tagName() == "audio")
                    _data.last().audio = e.text();
                else if (e.tagName() == "grapheme")
                    _data.last().graphemes.push_back(e.text());
                else if (e.tagName() == "sentence")
                    _data.push_back(Sentence());
                else if (e.tagName() == "translation")
                {
                    auto language = e.attribute("language", "");
                    // TODO Обработать ошибку
                    if ( !language.isEmpty() )
                        _data.last().translations[language] = e.text();
                    else
                        qDebug() << "XML parse error: tag" << e.tagName()
                                 << ", line " << e.lineNumber();
                }
            }
        }

        parser(current);
        current = current.nextSibling();
    }
}
