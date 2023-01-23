import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.0
import cursor 1.0
import QtQuick.LocalStorage 2.0
import "Database.js" as JS

Window {
    id: window
    visible: true
    width: 1280
    height: 720
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: "Block-Based Programming Language"
    Component.onCompleted: {
        JS.dbInit()
        Qt.createQmlObject('import QtQuick.Controls 2.5; StackView {
            id: stackView; anchors.fill: parent; initialItem: "Tasks.qml";
            function foo() { console.log("Current page has changed") }}', window, "window")
    }
    Cursor {
        id: curs
    }
}