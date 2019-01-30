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
#ifndef SENTENCE_H
#define SENTENCE_H

#include <QAbstractListModel>
#include "Word.h"

/*
 * Represents sentence in exercise.
 *
 * Each sentence gives un-ordered list of words which user could re-order.
 * In addition sentence gives interface to check if the order is correct.
 */
class Sentence : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        DataRole = Qt::UserRole + 1,
        ColorRole,
    };

    explicit Sentence(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void move(int from, int to);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QVector<Word> m_words;
};

#endif // SENTENCE_H
