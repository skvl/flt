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
                settings.userSirname = sirname.text
                settings.userName = name.text
                stack.pop()
            }

            Layout.alignment: Qt.AlignVCenter
        }
    }

    Column {
        Row {
            Text {
                text: qsTr("Material Light")

                fontSizeMode: Text.Fit
                minimumPointSize: 12
                font.pointSize: 20

                color: Material.foreground
                verticalAlignment: Text.AlignVCenter

                height: parent.height
                width: parent.width * 0.8
            }

            Switch {
                checked: "Light" === settings.theme

                onClicked: {
                    if (checked) {
                        Material.theme = Material.Light
                        settings.theme = "Light"
                    } else {
                        Material.theme = Material.Dark
                        settings.theme = "Dark"
                    }
                }

                anchors.right: parent.right

                height: parent.height
                width: parent.width * 0.2
            }

            height: Math.max(80, parent.height / 10)
            width: parent.width
        }

        ColumnLayout {
            Text {
                text: qsTr("Your name")

                fontSizeMode: Text.Fit
                minimumPointSize: 12
                font.pointSize: 20

                color: Material.foreground

                Layout.fillWidth: true
            }

            TextField {
                id: sirname

                placeholderText: qsTr("Sirname")

                font.pointSize: 14

                color: Material.foreground

                Layout.fillWidth: true
            }

            TextField {
                id: name

                placeholderText: qsTr("Name")

                font.pointSize: 14

                color: Material.foreground

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }

            height: Math.max(200, parent.height / 5)
            width: parent.width
        }

        anchors.margins: 10
        anchors.fill: parent

        spacing: 10
    }
}
