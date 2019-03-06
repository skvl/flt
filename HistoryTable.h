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
#ifndef HISTORYTABLE_H
#define HISTORYTABLE_H

#include <QAbstractTableModel>
#include "HistoryRecord.h"

class HistoryTable : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QVariantList columnHeaders READ columnHeaders CONSTANT)
    Q_PROPERTY(QVariantList rowHeaders READ rowHeaders CONSTANT)

public:
    explicit HistoryTable(QList<Record> list, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex & = QModelIndex()) const;
    int rowCount(const QModelIndex & = QModelIndex()) const;

    // Workaround
    QVariantList columnHeaders() const;
    QVariantList rowHeaders() const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Record> m_list;
};

#endif // HISTORYTABLE_H
