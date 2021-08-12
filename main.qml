import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: qsTr("Bếp")
    background: Rectangle {
            color: _BACKGOUND_COLOR
    }
    readonly property color _COLOR_RED: "#bc1823"
    readonly property color _COLOR_WHITE: "#ffffff"
    readonly property color _COLOR_WHITE_2: "#b3b3b3"
    readonly property color _BACKGOUND_COLOR: "#efefef"
    property var listViewModel: backend.data

    Item {
        id: header
        width: parent.width
        height: 50
        Text {
            id: headerText
            anchors.centerIn: parent
            text: "Bếp"
            font {
                bold: true
                pixelSize: 30
            }
            color: _COLOR_WHITE
        }
        Rectangle {
            anchors.fill: parent
            color: _COLOR_RED
            z: -1
        }
    }

    Item {
        id: container
        width: parent.width
        height: parent.height - header.height
        anchors.top: header.bottom
        anchors.topMargin: 30
        ListView {
            id: listView
            width: parent.width - 100
            anchors.horizontalCenter: parent.horizontalCenter
            height: parent.height
            model: listViewModel
            clip: true
            spacing: 10
            delegate: Item {
                width: listView.width
                height: 150
                // Ordinal numbers
                Text {
                    id: ordinalNumbers
                    width: 60
                    horizontalAlignment: Text.AlignHCenter
                    anchors {
                        verticalCenter: parent.verticalCenter
                        left: parent.left
                        leftMargin: 20
                    }
                    font {
                        pixelSize: 50
                    }
                    text: index + 1

                    Rectangle {
                        width: 3
                        height: parent.height
                        anchors{
                            verticalCenter: parent.verticalCenter
                            left: parent.right
                            leftMargin: 10
                        }
                        color: _COLOR_RED

                    }
                }
                // content of the orders
                Text {
                    id: contentData
                    anchors {
                        left: ordinalNumbers.right
                        leftMargin: 30
                        right: checkBtn.left
                        rightMargin: 30
                        verticalCenter: parent.verticalCenter
                    }
                    height: parent.height
                    text: modelData
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    font {
                        pixelSize: 25
                    }
                }

                // check button
                Image {
                    id: checkBtn
                    anchors {
                        right: parent.right
                        rightMargin: 30
                        verticalCenter: parent.verticalCenter
                    }
                    source: "image/checked.png"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: backend.removeDishFromData(index)
                    }
                }

                //background
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    color: index % 2 ? _COLOR_WHITE : _COLOR_WHITE_2
                    radius: height * 0.08
                }
            }
        }
    }
}
