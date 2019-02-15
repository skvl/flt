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
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.0

Page {
    header: ToolBar {
        ToolButton {
            text: qsTr("Home")

            onClicked: stack.pop()

            Layout.alignment: Qt.AlignVCenter
        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 10

        // From https://stackoverflow.com/a/17191620
        clip: true

        spacing: 20

        model: settings.getResults()

        delegate: Item {
            height: Math.min(120, width / 2)
            width: parent.width

            Column {
                anchors.fill: parent

                Rectangle {
                    Text {
                        id: name

                        text: "%1 %2".arg(settings.userSirname).arg(settings.userName)

                        fontSizeMode: Text.Fit
                        minimumPointSize: 8
                        font.pointSize: 1000

                        height: parent.height / 3
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"

                        anchors.top: parent.top
                    }

                    Text {
                        id: date

                        text: modelData.date

                        fontSizeMode: Text.Fit
                        minimumPointSize: 8
                        font.pointSize: 1000

                        height: parent.height / 3
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"

                        anchors.top: name.bottom
                    }

                    Text {
                        text: qsTr("Correct %1 of %2 during %3"
                                   .arg(modelData.correct)
                                   .arg(modelData.total)
                                   .arg(dataBase.elapsedToString(modelData.elapsed)))

                        fontSizeMode: Text.Fit
                        minimumPointSize: 8
                        font.pointSize: 1000

                        height: parent.height / 3
                        width: parent.width
                        horizontalAlignment: Text.AlignHCenter
                        color: "white"

                        anchors.top: date.bottom
                    }

                    radius: 25
                    color: Material.color(Material.BlueGrey)

                    anchors.left: parent.left
                    height: parent.height / 2
                    width: parent.width
                }
            }
        }
    }
}
