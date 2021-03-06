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

#include <QGuiApplication>

#include "HistoryRecord.h"
#include "HistoryTable.h"
#include "Settings.h"

const QHash<int, QString> Settings::keys{
    {AppInfo, "AppInfo"},
    {Language, "Language"},
    {Theme, "Theme"},
    {Level, "Level"},
    {UserInfo, "UserInfo"},
    {UserName, "Name"},
    {UserSirname, "Sirname"},
    {HistoryInfo, "HistoryInfo"},
    {HistoryCount, "Count"},
    {HistoryRecord, "Record "},
};

Settings::Settings(QQmlApplicationEngine *engine, const QString &organization, const QString &application, QObject *parent)
    : QSettings (organization, application, parent)
    , m_engine(engine)
{
    m_translator.load(":/translations/ru.qm");
}

Settings::~Settings()
{
    save();
}

QString Settings::userName() const
{
    return m_userName;
}

void Settings::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}

QString Settings::userSirname() const
{
    return m_userSirname;
}

void Settings::setUserSirname(const QString &userSirname)
{
    if (userSirname == m_userSirname)
        return;

    m_userSirname = userSirname;
    emit userSirnameChanged();
}

void Settings::save()
{
    beginGroup(keys[AppInfo]);
    setValue(keys[Language], m_language);
    setValue(keys[Theme], m_theme);
    setValue(keys[Level], m_level);
    endGroup();

    beginGroup(keys[UserInfo]);
    setValue(keys[UserName], m_userName);
    setValue(keys[UserSirname], m_userSirname);
    endGroup();
}

void Settings::load()
{
    QString defaultLocale = QLocale::system().name(); // e.g. "de_DE"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // e.g. "de"
    defaultLocale = defaultLocale.toUpper();

    beginGroup(keys[AppInfo]);
    m_language = value(keys[Language], defaultLocale).toString();
    m_theme = value(keys[Theme], "Light").toString();
    m_level = toLevels(value(keys[Level], 1).toInt());
    endGroup();

    beginGroup(keys[UserInfo]);
    m_userName = value(keys[UserName], "").toString();
    m_userSirname = value(keys[UserSirname], "").toString();
    endGroup();

    loadTranslator();
}

void Settings::saveResult(QDateTime date, int correct, int total, int elapsed)
{
    beginGroup(keys[HistoryInfo]);

    auto count = value(keys[HistoryCount], 0).toInt() + 1;
    setValue(keys[HistoryCount], count);

    auto k = keys[HistoryRecord] + QString::number(count);
    auto v = QString("DATE:%1 SIRNAME:%2 NAME:%3 CORRECT:%4 TOTAL:%5 ELAPSED:%6 LEVEL:%7")
            .arg(date.toString("yyyyMMddHHmmss"))
            .arg(m_userSirname)
            .arg(m_userName)
            .arg(correct)
            .arg(total)
            .arg(elapsed)
            .arg(m_level);
    setValue(k, v);

    endGroup();
}

QString Settings::theme() const
{
    return m_theme;
}

void Settings::setTheme(const QString &theme)
{
    if (theme == m_theme)
        return;

    m_theme = theme;
    emit themeChanged();
}

QVariant Settings::history()
{
    QList<Record> r;

    beginGroup(keys[HistoryInfo]);

    auto c = value(keys[HistoryCount], 0).toInt();

    for (auto i = 1; i <= c; ++i)
    {
        auto v = value(keys[HistoryRecord] + QString::number(i), QString()).toString();
        if (!v.isEmpty())
        {
            auto name = parseValue(v, "NAME");
            auto sirname = parseValue(v, "SIRNAME");
            auto date = QDateTime::fromString(parseValue(v, "DATE"), "yyyyMMddHHmmss");
            auto correct = parseValue(v, "CORRECT").toInt();
            auto total = parseValue(v, "TOTAL").toInt();
            auto elapsed = parseValue(v, "ELAPSED").toInt();
            auto level = parseValue(v, "LEVEL").toInt();

            Record hr(name, sirname, date, correct, total, elapsed, level);

            r.push_back(hr);
        }
    }

    endGroup();

    return QVariant::fromValue(new HistoryTable(r));
}

int Settings::level() const
{
    return m_level;
}

void Settings::setLevel(const int level)
{
    auto l = toLevels(level);
    if (l == m_level)
        return;

    m_level = l;

    emit levelChanged();
    emit levelDescriptionChanged();
}

Settings::Levels Settings::toLevels(int level)
{
    switch (level) {
    default:
    case 1:
        return Audio;
    case 2:
        return Text;
    case 3:
        return NoClues;
    }
}

QString Settings::toString(enum Levels level)
{
    switch (level) {
    case Audio:
        return tr("Audio");
    case Text:
        return tr("Text");
    case NoClues:
        return tr("No Clues");
    }

    return tr("Audio");
}

QString Settings::toString(int level)
{
    return toString(toLevels(level));
}

QString Settings::levelDescription() const
{
    switch (m_level) {
    case Audio:
        return QString(tr("The simplest level: allows to listen the sentence."));
    case Text:
        return QString(tr("The medium level: displays the translated sentence."));
    case NoClues:
        return QString(tr("The hardest level: gives no clues to construct the sentence."));
    }

    return QString();
}

QString Settings::language() const
{
    return m_language;
}

void Settings::setLanguage(const QString &language)
{
    if (language == m_language)
        return;

    m_language = language;
    loadTranslator();
    emit languageChanged();
}

QString Settings::parseValue(QString kv, QString key) const
{
    QHash<QString, QString> map;
    
    auto paires = kv.split(" ");
    for (auto i: paires)
    {
        auto pair = i.split(":");
        map.insert(pair[0], pair[1]);
    }

    return map.value(key);
}

void Settings::loadTranslator()
{
    if ("RU" == m_language)
        qApp->installTranslator(&m_translator);
    else
        qApp->removeTranslator(&m_translator);

    m_engine->retranslate();
}
