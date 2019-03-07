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
import QtQuick.Controls.Material 2.0
import QtQml.Models 2.1
import QtMultimedia 5.0


Page {
    FontLoader {
        id: wordFont

        source: dataBase.wordFont
    }

    Audio {
        id: audio

        source: root.dataModel.audio
    }

    Rectangle {
        id: message

        property string text: ""

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 10
        height: 50; width: parent.width * 0.8
        radius: 3
        color: Material.primary
        visible: false
        z: 10

        onVisibleChanged: {
            if (visible)
                timer.running = true
        }

        Text {
            text: parent.text

            anchors.fill: parent
            anchors.margins: 5

            fontSizeMode: Text.Fit
            minimumPointSize: 8
            font.pointSize: 1000

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter

            color: "white"
        }

        Timer {
            id: timer

            interval: 1500
            running: false
            repeat: true

            onTriggered: message.visible = false
        }
    }

    header: ToolBar {
        ColumnLayout {
            RowLayout {
                ToolButton {
                    text: qsTr("Audio")
                    visible: 1 >= settings.level

                    onClicked: audio.play()

                    Layout.alignment: Qt.AlignVCenter
                }

                ToolButton {
                    text: qsTr("Previous")

                    onClicked: {
                        if (dataBase.first) {
                            message.text = qsTr("This is the first sentence.")
                            message.visible = true
                        } else
                            dataBase.previous()
                    }

                    Layout.alignment: Qt.AlignVCenter
                }

                ToolButton {
                    text: qsTr("Next")

                    onClicked: {
                        if (dataBase.last) {
                            message.text = qsTr("This is the last sentence.")
                            message.visible = true
                        } else
                            dataBase.next()
                    }

                    Layout.alignment: Qt.AlignVCenter
                }

                Label {
                    id: stopwatch

                    text: dataBase.elapsedToString(dataBase.elapsed)

                    horizontalAlignment: Text.AlignHCenter

                    Layout.alignment: Qt.AlignVCenter
                    Layout.fillWidth: true
                }

                ToolButton {
                    text: qsTr("Finish")

                    onClicked: stack.replace(Qt.resolvedUrl("Results.qml"))

                    Layout.alignment: Qt.AlignVCenter
                }

                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            Label {
                visible: 2 >= settings.level

                Layout.fillWidth: true

                text: root.dataModel.translation
            }

            anchors.fill: parent
        }
    }

    GridView {
        property var dataModel: dataBase.data

        onDataModelChanged: visualModel.model = dataModel

        id: root

        height: parent.height - 10
        width: parent.width - 10
        x: 5
        y: 5

        cellHeight: getSize()
        cellWidth: cellHeight

        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }

        model: DelegateModel {
            id: visualModel

            model: parent.dataModel

            delegate: MouseArea {
                property int visualIndex: DelegateModel.itemsIndex

                id: delegateRoot

                height: root.cellHeight
                width: root.cellWidth

                drag.target: block

                Rectangle {
                    id: block

                    objectName: "Block"

                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }

                    height: root.cellHeight - 8
                    width: root.cellWidth - 8
                    radius: width / 10

                    color: settings.level < 3 ? model.background : "blue"
                    Text {
                        anchors.fill: parent

                        fontSizeMode: Text.Fit
                        font.family: wordFont.name
                        minimumPointSize: 8
                        font.pointSize: 1000

                        text: model.data

                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter

                        color: settings.level < 3 ? model.foreground : "white"
                    }

                    Drag.active: delegateRoot.drag.active
                    Drag.source: delegateRoot
                    Drag.hotSpot.x: width / 2
                    Drag.hotSpot.y: width / 2

                    states: [
                        State {
                            when: block.Drag.active
                            ParentChange {
                                target: block
                                parent: root
                            }

                            AnchorChanges {
                                target: block;
                                anchors.horizontalCenter: undefined
                                anchors.verticalCenter: undefined
                            }
                        }

                    ]
                }

                DropArea {
                    anchors { fill: parent; margins: 15 }

                    onEntered: root.dataModel.move(drag.source.visualIndex, delegateRoot.visualIndex)
                }
            }
        }

        function getSize() {
            var minSize = 25

            if (model.count <= 0 || height <= 0 || width <= 0)
                return minSize

            var size = minSize
            var p = 0

            for (var rows = 1, columns = model.count;
                 rows <= model.count;
                 ++rows, columns = 1 + (model.count - 1) / rows)
            {
                var s = Math.min(height / rows, width / columns)

                if (s > size)
                    size = s

                if (s < p)
                    return size
                else
                    p = s
            }

            return size
        }
    }
}
