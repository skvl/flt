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

#include <QDir>
#include <QFileInfo>
#include <QXmlStreamReader>

#include "DataBase.h"

DataBase::DataBase(QString path, QObject *parent)
    : QObject (parent)
    , m_opened(false)
    , m_file(new QFile(path))
{
    connect(&m_timer, &QTimer::timeout, this, &DataBase::tick);
}

DataBase::~DataBase()
{
    // FIX The sentences are deleted somewhere else
//    for (auto s: m_data)
//        delete s;
}

void DataBase::open()
{
    QDir dir(QFileInfo(m_file->fileName()).absoluteDir());

    if (m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml(m_file);

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartDocument)
                continue;

            if (token == QXmlStreamReader::StartElement
                    && (xml.name() == "sentences"
                        || xml.name() == "info"))
                continue;

            if (token == QXmlStreamReader::StartElement
                    && xml.name() == "fonts")
            {
                while(!(xml.tokenType() == QXmlStreamReader::EndElement
                        && xml.name() == "fonts"))
                {
                    xml.readNext();

                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name() == "word")
                        {
                            xml.readNext();
                            m_wordFont = "file:" + dir.filePath(xml.text().toString());
                        }

                        xml.readNext();
                    }
                }
            }

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
                            audio = "file:" + dir.filePath(xml.text().toString());
                        }
                        else if (xml.name() == "graphemes")
                        {
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement
                                    && xml.name() == "graphemes"))
                            {
                                xml.readNext();

                                if (xml.tokenType() == QXmlStreamReader::StartElement)
                                {
                                    if (xml.name() == "grapheme")
                                    {
                                        auto bg = QColor("blue");
                                        auto fg = QColor("white");

                                        auto a = xml.attributes();

                                        if (a.hasAttribute("background"))
                                            bg = QColor(a.value("background").toString());

                                        if (a.hasAttribute("foreground"))
                                            fg = QColor(a.value("foreground").toString());

                                        xml.readNext();

                                        auto w = Word(index++, xml.text().toString(), bg, fg);
                                        sentence.push_back(w);
                                    }

                                    xml.readNext();
                                }
                            }
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

QString DataBase::wordFont() const
{
    return m_wordFont;
}

QString DataBase::audio()
{
    return take()->audio();
}

QVariant DataBase::data()
{
    return QVariant::fromValue(take());
}

QString DataBase::translation()
{
    return take()->translation();
}

bool DataBase::first()
{
    if (m_data.begin() == m_iterator)
        return true;
    return false;
}

bool DataBase::last()
{
    if (m_data.end() == m_iterator + 1)
        return true;
    return false;
}

Sentence *DataBase::take()
{
    if (m_data.begin() == m_iterator)
        timerStart();

    Sentence* v = nullptr;

    if (m_opened && m_iterator < m_data.end())
        v = *m_iterator;

    return v;
}

void DataBase::next()
{
    if (m_iterator + 1 < m_data.end()) {
        m_iterator++;
        emit dataChanged();
        emit firstChanged();
        emit lastChanged();
    }
}

void DataBase::previous()
{
    if (m_iterator - 1 >= m_data.begin()) {
        m_iterator--;
        emit dataChanged();
        emit firstChanged();
        emit lastChanged();
    }
}

void DataBase::flush()
{
    if (!m_opened)
        return;

    std::random_device r;
    std::default_random_engine rng(r());
    std::shuffle(m_data.begin(), m_data.end(), rng);

    m_iterator = m_data.begin();
    m_wrong = m_data.begin();
}

int DataBase::count() const
{
    return m_data.count();
}

int DataBase::correctCount() const
{
    int wrong = 0;

    for (auto s: m_data)
        if (s->wrong())
            ++wrong;

    return m_data.count() - wrong;
}

QVariantList DataBase::allWrong()
{
    timerStop();

    QVariantList v;

    for (auto i = m_data.begin(); i <= m_iterator; ++i)
        if ((*i)->wrong())
            v.append(QVariant::fromValue(*i));

    return v;
}

void DataBase::timerStart()
{
    m_date = QDateTime::currentDateTime();
    emit dateChanged();

    m_time.start();
    m_timer.start(100);
}

void DataBase::timerStop()
{
    m_timer.stop();

    m_elapsed = m_time.elapsed();
}

QDateTime DataBase::date() const
{
    return m_date;
}

int DataBase::elapsed() const
{
    return m_elapsed;
}

QString DataBase::elapsedToString(int elapsed)
{
    int s = elapsed / 1000;
    int m = (s / 60) % 60;
    int h = s / 3600;
    s %= 60;

    return QString("%1:%2:%3")
            .arg(h, 2, 10, QLatin1Char('0'))
            .arg(m, 2, 10, QLatin1Char('0'))
            .arg(s, 2, 10, QLatin1Char('0'));
}

void DataBase::tick()
{
    m_elapsed = m_time.elapsed();
    elapsedChanged();
}

