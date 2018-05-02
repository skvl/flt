#include "exercisedata.h"

#include <QDebug>

ExerciseData::ExerciseData()
    : _data(QVector<Sentence>())
    , _iterator(_data.begin())
{
    QDomDocument doc;
    QFile file(":/exercies/Resources/Exercises/sentences.xml");

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
}

void ExerciseData::flush()
{
    _iterator = _data.begin();
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

QString ExerciseData::audio() const
{
    Q_ASSERT(_iterator < _data.end());
    return (*_iterator).audio;
}

QVector<QString> ExerciseData::graphemes() const
{
    Q_ASSERT(_iterator < _data.end());
    return (*_iterator).graphemes;
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
