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
import QtQuick.Layouts 1.0

Page {
    ColumnLayout {
        Button {
            text: qsTr("Start")

            onClicked: stack.push(Qt.resolvedUrl("Board.qml"))

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 60
            Layout.preferredWidth: 80
        }

        Button {
            text: qsTr("History")

            onClicked: stack.push(Qt.resolvedUrl("History.qml"))

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 60
            Layout.preferredWidth: 80
        }

        Button {
            text: qsTr("Settings")

            onClicked: stack.push(Qt.resolvedUrl("Settings.qml"))

            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 60
            Layout.preferredWidth: 80
        }

        anchors.fill: parent
        spacing: 5
    }
}
