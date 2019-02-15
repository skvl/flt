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
#ifndef HISTORYRECORD_H
#define HISTORYRECORD_H

#include <QDateTime>
#include <QObject>

class Record : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString date READ date CONSTANT)
    Q_PROPERTY(int correct READ correct CONSTANT)
    Q_PROPERTY(int total READ total CONSTANT)
    Q_PROPERTY(int elapsed READ elapsed CONSTANT)

public:
    explicit Record(QDateTime date, int correct, int total, int elapsed, QObject *parent = nullptr);

    QString date() const;

    int correct() const;

    int total() const;

    int elapsed() const;

private:
    QDateTime m_date;
    int m_correct;
    int m_total;
    int m_elapsed;
};

#endif // HISTORYRECORD_H
