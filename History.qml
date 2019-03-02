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

import QtQuick 2.12
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

    // It was quit difficult to deal with headers
    // Links:
    // - https://stackoverflow.com/a/27657021
    // - https://forum.qt.io/post/504932
    // - https://forum.qt.io/post/502134
    TableView {
            id: tableView

            columnWidthProvider: function (column) {
                return tableView.width / (tableView.columns + 1);
            }
            rowHeightProvider: function (column) { return 80; }
            anchors.fill: parent
            leftMargin: rowsHeader.implicitWidth
            topMargin: columnsHeader.implicitHeight
            model: settings.history
            delegate: Item {
                width: tableView.columnWidthProvider(modelData)
                Text {
                    id: txt
                    text: display
                    anchors.fill: parent
                    anchors.margins: 10

                    color: '#aaaaaa'
                    font.pixelSize: 15
                    verticalAlignment: Text.AlignVCenter

                    wrapMode: Text.Wrap
                    clip: true
                }

                x: index * tableView.columnWidthProvider(index)
            }

            Rectangle { // mask the headers
                z: 3
                color: "#222222"
                y: tableView.contentY
                x: tableView.contentX
                width: tableView.leftMargin
                height: tableView.topMargin
            }

            Row {
                id: columnsHeader
                y: tableView.contentY
                z: 2
                Repeater {
                    model: settings.history.columnHeaders
                    Label {
                        width: tableView.columnWidthProvider(modelData)
                        height: 35
                        text: modelData
                        color: '#aaaaaa'
                        font.pixelSize: 15
                        padding: 10
                        verticalAlignment: Text.AlignVCenter

                        background: Rectangle { color: "#333333" }

                        wrapMode: Text.Wrap
                        clip: true
                    }
                }
            }

            Column {
                id: rowsHeader
                x: tableView.contentX
                z: 2
                Repeater {
                    model: settings.history.rowHeaders
                    Label {
                        width: tableView.columnWidthProvider(modelData)
                        height: tableView.rowHeightProvider(modelData)
                        text: modelData
                        color: '#aaaaaa'
                        font.pixelSize: 15
                        padding: 10
                        verticalAlignment: Text.AlignVCenter

                        background: Rectangle { color: "#333333" }

                        wrapMode: Text.Wrap
                        clip: true
                    }
                }
            }

            ScrollIndicator.horizontal: ScrollIndicator { }
            ScrollIndicator.vertical: ScrollIndicator { }
        }
}
