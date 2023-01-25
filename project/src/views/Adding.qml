import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.0
import cursor 1.0
import noderesults 1.0
import board 1.0
import varnode 1.0
import printnode 1.0;
import "Database.js" as JS

Page {
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
                text: "HOME"
                onClicked: stackView.pop()
            }
            Button {
                text: "HELP"
                onClicked: help.open()
            }
            Text {
                id: goal
                color: "white"
                text: "Your goal: " + JS.getGoal("Adding.qml")
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

        RowLayout {
             anchors.right: parent.right
             anchors.rightMargin: 8
             Button {
                text: "CHANGE THEME"
                onClicked: {
                    board.darkTheme=!board.darkTheme
                    board.update()
                }
            }
            Button {
                text: "RUN"
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
                text: "Console"
                font.pointSize: 12
                font.italic: false
                font.bold: true
            }
        }
        ScrollView {
        anchors.fill: parent
        TextArea {
            id: outputText
            y: 34
            color: "#fdfdfd"
            text: "Here you will see the result of work"
            font.pixelSize: 18
            readOnly: true
        }}
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
                correctAnswer: JS.getGoal("Adding.qml")
                onCorrectAnswer: {
                    success.open()
                }
            }

            VarNode {
                x: 100
                y: 50
                destructible: false
                editable: false
                value: "2"
            }

            VarNode {
                x: 100
                y: 250
                destructible: false
                editable: false
                value: "2"
            }

            PrintNode {
                x: 1000
                y: 150
            }

            Dialog {
                id: success
                title: "Success"
                x: (window.width - width) / 2
                y: (window.height - height) / 2
                parent: ApplicationWindow.overlay
                standardButtons: StandardButton.Ok
                onAccepted: {
                    JS.completeTask("Adding.qml")
                    stackView.push("Tasks.qml")
                }
                Text {
                    text: "You have completed the task!"
                }
            }

            Menu {
                id: contextMenu
                cascade: true
                Menu {
                    title: "Math"
                    MenuItem {
                        text: "Add"
                        onClicked: {
                            Qt.createQmlObject('import addnode 1.0;
                                AddNode {x:'+curs.getCursor(window.x,window.y).x+'
                                        y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }

                    MenuItem {
                        text: "Subtract"
                        onClicked: {
                            Qt.createQmlObject('import subtractnode 1.0;
                                SubtractNode {x:'+curs.getCursor(window.x,window.y).x+'
                                        y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }

                    MenuItem {
                        text: "Multiply"
                        onClicked: {
                            Qt.createQmlObject('import multiplynode 1.0;
                                MultiplyNode {x:'+curs.getCursor(window.x,window.y).x+'
                                        y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }

                    MenuItem {
                        text: "Divide"
                        onClicked: {
                            Qt.createQmlObject('import dividenode 1.0;
                                DivideNode {x:'+curs.getCursor(window.x,window.y).x+'
                                        y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }

                    MenuItem {
                        text: "Modulo"
                        onClicked: {
                            Qt.createQmlObject('import modulonode 1.0;
                                ModuloNode {x:'+curs.getCursor(window.x,window.y).x+'
                                        y:'+curs.getCursor(window.x,window.y).y+' }', board, "board");
                        }
                    }
                }
            }
        }
    }
}