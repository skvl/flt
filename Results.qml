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

            onClicked: {
                dataBase.flush()
                stack.pop()
            }

            Layout.alignment: Qt.AlignVCenter
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 40

        Column {
            Text {
                text: qsTr("Your result is %1 of %2".arg(dataBase.correctCount()).arg(dataBase.count()))

                fontSizeMode: Text.Fit
                minimumPointSize: 12
                font.pointSize: 1000
                horizontalAlignment: Text.AlignHCenter

                color: Material.foreground

                height: parent.height * 0.6
                width: parent.width
            }

            Text {
                text: qsTr("Your time is XXX")

                fontSizeMode: Text.Fit
                minimumPointSize: 10
                font.pointSize: 1000
                horizontalAlignment: Text.AlignHCenter

                color: Material.foreground

                height: parent.height * 0.4
                width: parent.width
            }

            height: Math.min(80, parent.height / 10)
            width: parent.width
        }

        Button {
            text: qsTr("Details")

            onClicked: list.visible = !list.visible

            Layout.alignment: Qt.AlignHCenter
        }

        ListView {
            id: list

            visible: false

            // From https://stackoverflow.com/a/17191620
            clip: true

            spacing: 20

            Layout.fillHeight: true
            Layout.fillWidth: true

            model: dataBase.allWrong()

            delegate: Item {
                height: Math.min(120, width / 2)
                width: parent.width

                Column {
                    anchors.fill: parent

                    Rectangle {
                        Text {
                            text: modelData.result

                            fontSizeMode: Text.Fit
                            minimumPointSize: 8
                            font.pointSize: 1000

                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }

                        radius: 25
                        color: Material.color(Material.Red)

                        anchors.left: parent.left
                        height: parent.height / 2
                        width: parent.width
                    }

                    Rectangle {
                        Text {
                            text: modelData.origin

                            fontSizeMode: Text.Fit
                            minimumPointSize: 8
                            font.pointSize: 1000

                            anchors.fill: parent
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                        }

                        anchors.left: parent.left
                        height: parent.height / 2
                        width: parent.width
                        radius: 25
                        color: Material.color(Material.Green)
                    }
                }
            }
        }
    }
}
