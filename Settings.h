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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString userSirname READ userSirname WRITE setUserSirname NOTIFY userSirnameChanged)
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

public:
    Settings(const QString &organization, const QString &application = QString(), QObject *parent = nullptr);

    QString userName() const;
    void setUserName(const QString &userName);

    QString userSirname() const;
    void setUserSirname(const QString &userSirname);

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

    QString theme() const;
    void setTheme(const QString &theme);

signals:
    void userNameChanged();
    void userSirnameChanged();
    void themeChanged();

private:
    enum {
        AppInfo,
        Theme,
        UserInfo,
        UserName,
        UserSirname,
    };

    static const QHash<int, QString> keys;

    QString m_userName;
    QString m_userSirname;
    QString m_theme;
};

#endif // SETTINGS_H
