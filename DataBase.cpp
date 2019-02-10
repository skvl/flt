/*
 * Foreign Language Trainer is a program to study foreign languages through
 * various exercises.
 *
 * Copyright (C) 2019 Sergey Kovalev
 * https://github.com/skvl/flt

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <algorithm>
#include <random>

#include <QXmlStreamReader>

#include "DataBase.h"

DataBase::DataBase(QString path, QObject *parent)
    : QObject (parent)
    , m_opened(false)
    , m_file(new QFile(path))
    , m_path(path)
{
}

DataBase::~DataBase()
{
    // FIX The sentences are deleted somewhere else
//    for (auto s: m_data)
//        delete s;
}

void DataBase::open()
{
    if (m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml(m_file);

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartDocument)
                continue;

            if (token == QXmlStreamReader::StartElement
                    && xml.name() == "sentences")
                continue;

            if (token == QXmlStreamReader::StartElement
                    && xml.name() == "sentence")
            {
                int index = 0;
                QString audio;
                QVector<Word> sentence;
                QMap<QString, QString> translations;

                while(!(xml.tokenType() == QXmlStreamReader::EndElement
                        && xml.name() == "sentence"))
                {
                    xml.readNext();

                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name() == "audio")
                        {
                            xml.readNext();
                            audio = xml.text().toString();
                        }
                        else if (xml.name() == "grapheme")
                        {
                            xml.readNext();

                            auto bg = QColor("blue");
                            auto fg = QColor("white");

                            auto a = xml.attributes();
                            if (a.hasAttribute("background"))
                                bg = QColor(a.value("background").toUInt());
                            if (a.hasAttribute("foreground"))
                                fg = QColor(a.value("foreground").toUInt());

                            auto w = Word(index++, xml.text().toString(), bg, fg);
                            sentence.push_back(w);
                        }
                        else if (xml.name() == "translations")
                        {
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement
                                    && xml.name() == "translation"))
                            {
                                xml.readNext();

                                if (xml.tokenType() == QXmlStreamReader::StartElement)
                                {
                                    auto a = xml.attributes();
                                    if (a.hasAttribute("language"))
                                    {
                                        auto l = a.value("language").toString();
                                        xml.readNext();
                                        translations[l] = xml.text().toString();
                                    }
                                }
                            }
                        }

                        xml.readNext();
                    }
                }

                m_data.push_back(new Sentence(audio, sentence, translations));
            } // sentence parser
        }
    }

    m_opened = true;

    flush();
}

QVariant DataBase::take()
{
    QVariant v;

    if (m_opened && m_iterator < m_data.end())
        v = QVariant::fromValue(*m_iterator);

    return v;
}

QVariant DataBase::next()
{
    m_iterator++;
    return take();
}

void DataBase::flush()
{
    if (!m_opened)
        return;

    auto rng = std::default_random_engine {};
    std::shuffle(m_data.begin(), m_data.end(), rng);

    m_iterator = m_data.begin();
    m_wrong = m_data.begin();
}

int DataBase::count() const
{
    return m_data.count();
}

int DataBase::wrongCount() const
{
    int wrong = 0;

    for (auto s: m_data)
        if (s->wrong())
            ++wrong;

    return wrong;
}

QVariant DataBase::nextWrong()
{
    if (m_wrong > m_data.begin() && m_wrong < m_data.end())
        ++m_wrong;

    for (; m_wrong < m_data.end(); ++m_wrong)
        if ((*m_wrong)->wrong())
            return QVariant::fromValue(*m_wrong);

    return QVariant();
}
