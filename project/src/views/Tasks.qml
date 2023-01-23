import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.0
import QtQuick.LocalStorage 2.0
import cursor 1.0
import noderesults 1.0
import board 1.0
import "Database.js" as JS

Page {
    id: tasks
    background: BorderImage {
        source: "../images/wmii.jpg"
    }
    ToolBar {
        id: toolBar
        height: 49
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        RowLayout {
            Button {
                text: "HELP"
                onClicked: help.open()
            }
            Text {
                id: welcome
                color: "white"
                text: "Hello " + JS.getUserName()
            }
        }

        Dialog {
            id: help
            title: "Help"
            x: (window.width - width) / 2
            y: (window.height - height) / 2
            parent: ApplicationWindow.overlay
            ColumnLayout {
                Text {
                    text: "1. Select task to do\n"
                }
                Text {
                    text: "Still do you need help?\ncontact@damian-tomczak.pl"
                }
                Text {
                    text: "University project made by:\nDamian Tomczak\nDominik Słodkowski\nBartosz Rybiński"
                }
            }

            standardButtons: StandardButton.Ok
        }
    }

    Rectangle {
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width/4
        height: parent.height/3
        radius: 10
        ListView {
            anchors.left: parent.left
            anchors.leftMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 10
            header: headertsr
            ScrollBar.vertical: ScrollBar {
                active: true
            }
            ListModel {
                id: listModel
                Component.onCompleted: {
                    JS.getAllTasks()
                }
            }

            Component {
                id: nameDelegate
                Button {
                    text: name
                    implicitWidth: 200
                    implicitHeight: 75
                    onClicked: stackView.push(url)
                }
            }

            spacing: 5
            anchors.fill: parent
            clip: true
            model: listModel
            delegate: nameDelegate
        }

        Component {
            id: headertsr
            Text {
                text: "Available tasks:"
                font.pointSize: 12
            }
        }
    }
}