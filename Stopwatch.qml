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

import QtQuick 2.0
import QtQuick.Controls 2.0

Label {
    property double startTime: new Date().getTime()

    text: "00:00:00"

    Timer {
        interval: 1000; running: true; repeat: true

        onTriggered: {
            var t = ((new Date().getTime() - parent.startTime) / 1000) | 0

            var h = (t / 3600) | 0
            var m = ((t - h * 3600) / 60) | 0
            var s = (t - m * 60) | 0

            if (h < 10)
                h = "0" + h
            if (m < 10)
                m = "0" + m
            if (s < 10)
                s = "0" + s

            parent.text = h + ":" + m + ":" + s
        }
    }
}
