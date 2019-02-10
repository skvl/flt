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
    header: ToolBar {
        RowLayout {
            ToolButton {
                text: qsTr("<")

                onClicked: stack.pop()

                Layout.alignment: Qt.AlignVCenter
            }

            Item {
                RowLayout {
                    Label {
                        text: dataBase.wrongCount()
                    }

                    Label {
                        text: qsTr("/")
                    }

                    Label {
                        text: dataBase.count()
                    }
                }

                Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
                Layout.fillWidth: true
            }
        }
    }

    ListView {
        anchors.fill: parent
        spacing: 10

        model: dataBase.allWrong()

        delegate: Item {
            height: Math.min(120, width / 2)
            width: parent.width

            RowLayout {
                anchors.fill: parent

                Rectangle {
                    Layout.alignment: Qt.AlignTop
                    height: 20
                    width: 20
                    radius: 2
                    border {
                        color: "black"
                        width: 1
                    }

                    Text {
                        text: index

                        fontSizeMode: Text.Fit
                        minimumPointSize: 8
                        font.pointSize: 1000

                        anchors.fill: parent

                        horizontalAlignment: Qt.AlignHCenter
                        verticalAlignment: Qt.AlignVCenter
                    }
                }

                Column {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Rectangle {
                        Text {
                            text: modelData.result

                            fontSizeMode: Text.Fit
                            minimumPointSize: 8
                            font.pointSize: 1000

                            anchors.fill: parent
                        }

                        radius: 2
                        color: "red"
                        border {
                            color: "black"
                            width: 1
                        }

                        anchors.left: parent.left
                        height: parent.height / 2
                        width: parent.width - 20
                    }

                    Rectangle {
                        Text {
                            text: modelData.origin

                            fontSizeMode: Text.Fit
                            minimumPointSize: 8
                            font.pointSize: 1000

                            anchors.fill: parent
                        }

                        anchors.right: parent.right
                        height: parent.height / 2
                        width: parent.width - 20
                        radius: 2
                        color: "green"
                        border {
                            color: "black"
                            width: 1
                        }
                    }
                }
            }
        }
    }
}
