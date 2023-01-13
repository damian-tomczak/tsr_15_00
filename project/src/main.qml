﻿import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.0
import cursor 1.0
import noderesults 1.0
import board 1.0

Window {
    id: window
    visible: true
    width: 1280
    height: 720
    title: "Block-Based Programming Language"

    Cursor
    {
        id: curs
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
        Button {
            text: "HELP"
            onClicked: help.open()
        }

        Dialog {
            id: help
            title: "Help"
            x: (window.width - width) / 2
            y: (window.height - height) / 2
            parent: ApplicationWindow.overlay
            ColumnLayout {
                Text {
                    text: "1. Click Right Mouse Button to see nodes to select\n2. If needed insert data into a created node\n3. Drag and drop ports\n4. Click 'RUN' button\n"
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

        Button {
            x: 514
            y: -1
            width: 118
            height: 50
            text: "RUN"
            anchors.right: parent.right
            anchors.rightMargin: 8
            onClicked: {
                var msg = calc.getResult(board)
                if(msg.indexOf("ERR")>=0) {
                    outputText.color="red"
                    msg=msg.replace("ERR","")
                }
                else {
                    outputText.color="white"
                }
                outputText.text=msg
            }
        }
    }

    Rectangle {
        id: consolePanel
        x: 0
        y: 353
        height: 127
        color: "#353533"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        Rectangle {
            id: consoleHeaderPanel
            x: 0
            y: 0
            height: 35
            color: "#078493"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 92
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            Label {
                id: label
                x: 8
                y: 8
                color: "#deffffff"
                text: qsTr("Console")
                font.pointSize: 12
                font.italic: false
                font.bold: true
            }
        }

        TextEdit {
            id: outputText
            y: 34
            height: 93
            color: "#fdfdfd"
            text: qsTr("Here you will see the result of work")
            font.italic: false
            font.bold: false
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.pixelSize: 18
        }
    }

    Rectangle {
        id: mainWorkingPanel
        color: "#eaea7e"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 123
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 46

        Board {
            id: board
            objectName: "board"
            anchors.fill: parent
            onRightClickedChanged: if(board.rightClicked) contextMenu.popup()
            Result {
                id: calc
            }

            Menu {
                id: contextMenu
                cascade: true
                Menu {
                    title: "Input"
                    MenuItem {
                        text: "1D Var"
                        onClicked: {
                            var newObject = Qt.createQmlObject('import var1dnode 1.0;
                                    Var1DNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }

                }

                Menu
                {
                    title: "Math"
                        MenuItem {
                            text: "Add"
                            onClicked: {
                                var newObject = Qt.createQmlObject('import addnode 1.0;
                                    AddNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                            }
                        }

                        MenuItem {
                            text: "Subtract"
                            onClicked: {
                                var newObject = Qt.createQmlObject('import subtractnode 1.0;
                                    SubtractNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                            }
                        }

                        MenuItem {
                            text: "Multiply"
                            onClicked: {
                                var newObject = Qt.createQmlObject('import multiplynode 1.0;
                                    MultiplyNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                            }
                        }

                        MenuItem {
                            text: "Divide"
                            onClicked: {
                                var newObject = Qt.createQmlObject('import dividenode 1.0;
                                    DivideNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                            }
                        }

                        MenuItem {
                            text: "Modulo"
                            onClicked: {
                                var newObject = Qt.createQmlObject('import modulonode 1.0;
                                    ModuloNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                            }
                        }
                }

                Menu {
                    title: "Output"

                    MenuItem {
                        text:"Print"
                        onClicked: {
                            var newObject = Qt.createQmlObject('import printnode 1.0;
                                    PrintNode {x:'+curs.getCursor(window.x,window.y).x+'
                                         y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }
                }
            }
        }
    }
}
