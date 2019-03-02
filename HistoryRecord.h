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

class Record
{
public:
    explicit Record(QString name,
                    QString sirname,
                    QDateTime date,
                    int correct,
                    int total,
                    int elapsed,
                    QString level);

    QString name() const;

    QString sirname() const;

    QDateTime date() const;

    int correct() const;

    int total() const;

    int elapsed() const;

    QString level() const;

private:
    QString m_name;
    QString m_sirname;
    QDateTime m_date;
    int m_correct;
    int m_total;
    int m_elapsed;
    QString m_level;
};

#endif // HISTORYRECORD_H
