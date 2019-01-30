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

DataBase::DataBase(QString path)
    : m_path(path)
{
}

void DataBase::open()
{
    QDomDocument doc;
    QFile file(m_path);

    if (file.open(QIODevice::ReadOnly))
    {
        auto errorMessage = QString("");
        int errorLine = 0;
        int errorColumn = 0;

        if (doc.setContent(&file, &errorMessage, &errorLine, &errorColumn))
        {
            parser(doc.documentElement());
        }
        else
            qDebug() << errorMessage << errorLine << errorColumn;
    }
    else
        qDebug() << "Failed to open file";
}

void DataBase::parser(const QDomNode &node)
{
    QDomNode current = node.firstChild();

    while ( !current.isNull() )
    {
        if ( current.isElement() )
        {
            QDomElement e = current.toElement();

            if ( !e.isNull() )
            {
                if (e.tagName() == "audio")
                    m_data.last().audio = e.text();
                else if (e.tagName() == "grapheme")
                    m_data.last().graphemes.push_back(e.text());
                else if (e.tagName() == "sentence")
                    m_data.push_back(Sentence());
                else if (e.tagName() == "translation")
                {
                    auto language = e.attribute("language", "");
                    // TODO Обработать ошибку
                    if ( !language.isEmpty() )
                        m_data.last().translations[language] = e.text();
                    else
                        qDebug() << "XML parse error: tag" << e.tagName()
                                 << ", line " << e.lineNumber();
                }
            }
        }

        parser(current);
        current = current.nextSibling();
    }
}
