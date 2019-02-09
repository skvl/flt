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

#ifndef WORD_H
#define WORD_H

#include <QColor>
#include <QString>

/*
 * Represents single word in a sentence.
 *
 * Each word contains data string and optional color.
 */

class Word
{
public:
    Word(int index = 0, QString data = QString(), QColor background = QColor(), QColor foreground = QColor());

    int index();
    QString data() const;
    QColor  background() const;
    QColor foreground() const;

private:
    int     m_index;
    QString m_data;
    QColor  m_background;
    QColor  m_foreground;
};

#endif // WORD_H
