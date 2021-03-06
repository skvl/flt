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
#include "HistoryRecord.h"

Record::Record(QString name,
               QString sirname,
               QDateTime date,
               int correct,
               int total,
               int elapsed,
               int level)
    : m_name(name)
    , m_sirname(sirname)
    , m_date(date)
    , m_correct(correct)
    , m_total(total)
    , m_elapsed(elapsed)
    , m_level(level)
{
}

QString Record::name() const
{
    return m_name;
}

QString Record::sirname() const
{
    return m_sirname;
}

QDateTime Record::date() const
{
    return m_date;
}

int Record::correct() const
{
    return m_correct;
}

int Record::total() const
{
    return m_total;
}

int Record::elapsed() const
{
    return m_elapsed;
}

int Record::level() const
{
    return m_level;
}
