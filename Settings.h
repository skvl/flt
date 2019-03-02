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

#include <QDateTime>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTranslator>

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString userSirname READ userSirname WRITE setUserSirname NOTIFY userSirnameChanged)
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(QVariant history READ history NOTIFY historyChanged)
    Q_PROPERTY(QString level READ level WRITE setLevel NOTIFY levelChanged)
    Q_PROPERTY(QString levelDescription READ levelDescription NOTIFY levelDescriptionChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    Settings(QQmlApplicationEngine *engine, const QString &organization, const QString &application = QString(), QObject *parent = nullptr);
    ~Settings();

    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

    Q_INVOKABLE void saveResult(QDateTime date, int correct, int total, int elapsed);

    QString userName() const;
    void setUserName(const QString &userName);

    QString userSirname() const;
    void setUserSirname(const QString &userSirname);

    QString theme() const;
    void setTheme(const QString &theme);

    QVariant history();

    QString level() const;
    void setLevel(const QString &level);

    QString levelDescription() const;

    QString language() const;
    void setLanguage(const QString &language);

signals:
    void userNameChanged();
    void userSirnameChanged();
    void themeChanged();
    void historyChanged();
    void levelChanged();
    void levelDescriptionChanged();
    void languageChanged();

private:
    enum {
        AppInfo,
        Language,
        Theme,
        Level,
        UserInfo,
        UserName,
        UserSirname,
        HistoryInfo,
        HistoryCount,
        HistoryRecord,
    };

    static const QHash<int, QString> keys;

    QString m_userName;
    QString m_userSirname;
    QString m_language;
    QString m_theme;
    QString m_level;
    QList<QString> m_levelDescription;

    QTranslator m_translator;
    QQmlApplicationEngine *m_engine;

    QString parseValue(QString kv, QString key) const;
    void loadTranslator();
};

#endif // SETTINGS_H
