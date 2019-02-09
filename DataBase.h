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
#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>

#include "Sentence.h"

class DataBase
{
public:
    DataBase(QString path);
    ~DataBase();

    // Open DataBase.
    void open();
    // Get next sentece
    Sentence* next();
    // Re-order sentences and start from begin
    void flush();

private:
    bool m_opened;
    QFile* m_file;

    QVector<Sentence*> m_data;
    QVector<Sentence*>::iterator m_iterator;
};

#endif // DATABASE_H
