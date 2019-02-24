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

#include <QDateTime>
#include <QFile>
#include <QObject>
#include <QTime>
#include <QTimer>

#include "Sentence.h"

class DataBase : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int elapsed READ elapsed NOTIFY elapsedChanged)
    Q_PROPERTY(QDateTime date READ date NOTIFY dateChanged)
    Q_PROPERTY(QVariant data READ data NOTIFY dataChanged)
    Q_PROPERTY(QString audio READ audio NOTIFY audioChanged)
    Q_PROPERTY(QString wordFont READ wordFont CONSTANT)

public:
    DataBase(QString path = QString(), QObject *parent = nullptr);
    ~DataBase();

    // Open DataBase.
    void open();
    // Get fonts
    QString wordFont() const;
    // Get current sentence
    QString audio();
    QVariant data();
    // Get next sentece
    Q_INVOKABLE void next();
    // Get next sentece
    Q_INVOKABLE void previous();
    // Re-order sentences and start from begin
    Q_INVOKABLE void flush();

    // TODO Use Q_PROPERTY
    // Get total number of sentences
    Q_INVOKABLE int count() const;
    // Get number of wrong sentences
    Q_INVOKABLE int correctCount() const;
    // Get list of wrong sentences
    Q_INVOKABLE QVariantList allWrong();

    // Time management
    Q_INVOKABLE void timerStart();
    Q_INVOKABLE void timerStop();

    // Date and time of exercise start
    QDateTime date() const;
    // How much time elapsed from exercise start
    int elapsed() const;
    static Q_INVOKABLE QString elapsedToString(int elapsed);

signals:
    void elapsedChanged();
    void dateChanged();
    void dataChanged();
    void audioChanged();

private slots:
    void tick();

private:
    bool m_opened;
    QFile* m_file;

    QVector<Sentence*> m_data;
    QVector<Sentence*>::iterator m_iterator;
    QVector<Sentence*>::iterator m_wrong;

    QString m_wordFont;

    QDateTime m_date;
    QTime m_time;
    // TODO Use QObject timer instead
    QTimer m_timer;
    int m_elapsed;

    Sentence* take();
};

#endif // DATABASE_H
