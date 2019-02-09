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
#include <QXmlStreamReader>

#include "DataBase.h"

DataBase::DataBase(QString path)
    : m_file(new QFile(path))
{
}

DataBase::~DataBase()
{

}

void DataBase::open()
{
    if (m_file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QXmlStreamReader xml(m_file);

        while (!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartDocument)
                continue;

            if (token == QXmlStreamReader::StartElement
                    && xml.name() == "sentences")
                continue;

            if (token == QXmlStreamReader::StartElement
                    && xml.name() == "sentence")
            {
                int index = 0;
                QString audio;
                QVector<Word> sentence;
                QMap<QString, QString> translations;

                while(!(xml.tokenType() == QXmlStreamReader::EndElement
                        && xml.name() == "sentence"))
                {
                    xml.readNext();

                    if (xml.tokenType() == QXmlStreamReader::StartElement)
                    {
                        if (xml.name() == "audio")
                        {
                            audio = xml.text().toString();
                        }
                        else if (xml.name() == "grapheme")
                        {
                            auto bg = QColor();
                            auto fg = QColor();

                            auto a = xml.attributes();
                            if (a.hasAttribute("background"))
                                bg = QColor(a.value("background").toUInt());
                            if (a.hasAttribute("foreground"))
                                fg = QColor(a.value("foreground").toUInt());

                            auto w = Word(index++, xml.text().toString(), bg, fg);
                            sentence.push_back(w);
                        }
                        else if (xml.name() == "translation")
                        {
                            auto a = xml.attributes();
                            if (a.hasAttribute("language"))
                            {
                                auto l = a.value("language").toString();
                                translations[l] = xml.text().toString();
                            }
                        }

                        xml.readNext();
                    }
                }

                m_data.push_back(new Sentence(audio, sentence, translations));
            } // sentence parser
        }
    }
}
