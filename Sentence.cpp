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

#include "Sentence.h"

Sentence::Sentence(QString audio,
                   QVector<Word> sentence,
                   Translations translations,
                   QObject *parent)
    : QAbstractListModel(parent)
    , m_audio(audio)
    , m_sentence(sentence)
    , m_translations(translations)
{
    for (auto w: m_sentence)
        m_origin += w.data();

    std::random_device r;
    std::default_random_engine rng(r());
    std::shuffle(m_sentence.begin(), m_sentence.end(), rng);
}

int Sentence::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_sentence.count();
}

QVariant Sentence::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_sentence.count())
        return QVariant();

    const Word &w = m_sentence[index.row()];
    if (DataRole == role)
        return w.data();
    else if (BackgroundRole == role)
        return w.background();
    else if (ForegroundRole == role)
        return w.foreground();

    return QVariant();
}

void Sentence::move(int from, int to)
{
    if (from == to || from < 0 || from >= m_sentence.count() || to < 0 || to >= m_sentence.count())
        return;

    /*
     * Read carefully:
     * - https://doc.qt.io/qt-5/qabstractitemmodel.html#beginMoveRows
     * - https://bugreports.qt.io/browse/QTBUG-6940
     */

//    int destinationChild = to;
//    if (destinationChild > from)
//        ++destinationChild;
//    else if (destinationChild > 0)
//        --destinationChild;
//    beginMoveRows(QModelIndex(), from, from, QModelIndex(), destinationChild);
//    ...
//    endMoveRows();

    // Because of smooth animation in GridView it sometimes difficult to guess
    // the correct indexes so hard reset the model with new indexes
    beginResetModel();
    auto b = m_sentence.takeAt(from);
    m_sentence.insert(to, b);
    endResetModel();
}

QString Sentence::audio() const
{
    return m_audio;
}

QString Sentence::translation() const
{
    return m_translations["RU"];
}

bool Sentence::wrong() const
{
    for (auto w: m_sentence)
        if (w.data() != m_sentence.at(w.index()).data())
            return true;

    return false;
}

QString Sentence::origin() const
{
    return m_origin;
}

QString Sentence::result() const
{
    QString v;

    for (auto w: m_sentence)
        v += w.data();

    return v;
}

QHash<int, QByteArray> Sentence::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DataRole] = "data";
    roles[BackgroundRole] = "background";
    roles[ForegroundRole] = "foreground";
    return roles;
}
