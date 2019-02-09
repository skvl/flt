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
#include "Word.h"

Word::Word(int index, QString data, QColor background, QColor foreground)
    : m_index(index)
    , m_data(data)
    , m_background(background)
    , m_foreground(foreground)
{
}

int Word::index()
{
    return m_index;
}

QString Word::data() const
{
    return m_data;
}

QColor Word::background() const
{
    return m_background;
}

QColor Word::foreground() const
{
    return m_foreground;
}
