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

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

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

    if (!m_file->open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonDocument doc(QJsonDocument::fromJson(m_file->readAll()));
    if (!doc.isObject()) {
        qWarning("Malformed JSON file!");
        return;
    }

    /********************
     * Parse basic info *
     *******************/
    auto info = doc["info"];
    if (info.isUndefined()) {
        qWarning("No 'info'!");
        return;
    }

    auto fonts = info["fonts"];
    if (fonts.isUndefined()) {
        qWarning("No 'fonts'!");
        return;
    }

    m_wordFont = dir.filePath(fonts["grapheme"].toString());
    if (m_wordFont.isNull() || !QFileInfo(m_wordFont).exists()) {
        qWarning("No grapheme font!");
        return;
    }
    m_wordFont = "file:" + m_wordFont;

    /*******************
     * Parse sentences *
     ******************/
    auto s = doc["sentences"];
    if (!s.isArray()) {
        qWarning("No sentences array!");
        return;
    }

    for (auto sv: s.toArray()) {
        auto so = sv.toObject();
        if (so.isEmpty()) {
            qWarning("Sentence is not an object!");
            return;
        }

        QString audio = dir.filePath(so["audio"].toString());
        if (audio.isEmpty() || !QFileInfo(audio).exists()) {
            qWarning("No audio!");
            return;
        }
        audio = "file:" + audio;

        int lesson = so["lesson"].toInt(-1);
        int dialog = so["dialog"].toInt(-1);
        if (-1 == lesson || -1 == dialog) {
            qWarning("No lesson or dialog");
            return;
        }

        QVector<Word> graphemes;
        for (auto gv: so["graphemes"].toArray()) {
            auto go = gv.toObject();
            if (go.isEmpty()) {
                qWarning("Malformed JSON file: grapheme is not an object!");
                return;
            }

            QColor bg = QColor(go["background"].toString("blue"));
            QColor fg = QColor(go["foreground"].toString("white"));

            QString g = go["grapheme"].toString();
            if (g.isEmpty()) {
                qWarning("Malformed JSON file: no grapheme!");
                return;
            }

            graphemes.push_back(Word(graphemes.count(), g, bg, fg));
        }

        QMap<QString, QString> translations;
        for (auto tv: so["translations"].toArray()) {
            auto to = tv.toObject();
            if (to.isEmpty()) {
                qWarning("Malformed JSON file: translation is not an object!");
                return;
            }

            QString l = to["language"].toString();
            QString t = to["translation"].toString();
            if (l.isEmpty() || t.isEmpty() || translations.contains(l)) {
                qWarning("Malformed JSON file: empty language or translation or redudant translation!");
                return;
            }

            translations[l] = t;
        }

        m_data.push_back(new Sentence(audio, graphemes, translations));
    }

    /***************
     * Parse words *
     **************/

    /*******
     * End *
     ******/
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

