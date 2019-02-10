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

#include "Settings.h"

const QHash<int, QString> Settings::keys{
    {UserInfo, "UserInfo"},
    {UserName, "Name"},
    {UserSirname, "Sirname"},
};

Settings::Settings(const QString &organization, const QString &application, QObject *parent)
    : QSettings (organization, application, parent)
{

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
    beginGroup(keys[UserInfo]);
    setValue(keys[UserName], m_userName);
    setValue(keys[UserSirname], m_userSirname);
    endGroup();
}

void Settings::load()
{
    beginGroup(keys[UserInfo]);
    m_userName = value(keys[UserName], "").toString();
    m_userSirname = value(keys[UserSirname], "").toString();
    endGroup();
}
