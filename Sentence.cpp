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
#include "Sentence.h"

Sentence::Sentence(QObject *parent) : QAbstractListModel(parent)
{
}

int Sentence::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_words.count();
}

QVariant Sentence::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_words.count())
        return QVariant();

    const Word &block = m_words[index.row()];
    if (DataRole == role)
        return block.data();
    else if (ColorRole == role)
        return block.color();

    return QVariant();
}

void Sentence::move(int from, int to)
{
    if (from == to || from < 0 || from >= m_words.count() || to < 0 || to >= m_words.count())
        return;

    /*
     * Read carefully:
     * - https://doc.qt.io/qt-5/qabstractitemmodel.html#beginMoveRows
     * - https://bugreports.qt.io/browse/QTBUG-6940
     */
    int destinationChild = to;
    if (destinationChild - from == 1)
        ++destinationChild;

    beginMoveRows(QModelIndex(), from, from, QModelIndex(), destinationChild);
    auto b = m_words.takeAt(from);
    m_words.insert(to, b);
    endMoveRows();
}

QHash<int, QByteArray> Sentence::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DataRole] = "data";
    roles[ColorRole] = "color";
    return roles;
}
