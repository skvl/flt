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

#include "DataBase.h"
#include "HistoryTable.h"
#include "Settings.h"

QVariantList HistoryTable::m_columnHeaders = {
    tr("Date"), tr("Score"), tr("Elapsed"), tr("Level")
};

HistoryTable::HistoryTable(QList<Record> list, QObject *parent)
    : QAbstractTableModel(parent)
    , m_list(list)
{
}

int HistoryTable::rowCount(const QModelIndex &) const
{
    return m_list.count();
}

QVariantList HistoryTable::columnHeaders() const
{
    QVariantList v;
    for (auto i: m_columnHeaders)
        v.append(tr(qPrintable(i.toString())));
    return v;
}

QVariantList HistoryTable::rowHeaders() const
{
    QVariantList v;

    for (auto i: m_list)
        v << QString("%1 %2").arg(i.sirname()).arg(i.name());

    return v;
}

int HistoryTable::columnCount(const QModelIndex &) const
{
    return m_columnHeaders.count();
}

QVariant HistoryTable::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_list.count())
        return QVariant();

    auto v = &m_list[index.row()];
    switch (role) {
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0:
            return QString("%1\n%2")
                    .arg(v->date().toString("dd.MM.yyyy"))
                    .arg(v->date().toString("mm:HH"));
        case 1:
            return QString(tr("%1 of %2"))
                    .arg(v->correct())
                    .arg(v->total());
        case 2:
            return DataBase::elapsedToString(v->elapsed());
        case 3:
            return Settings::toString(v->level());
        }
        break;

    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> HistoryTable::roleNames() const
{
    return QHash<int, QByteArray> {
        {Qt::DisplayRole, "display"},
    };
}
