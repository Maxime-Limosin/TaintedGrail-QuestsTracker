import QtQuick

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        height: 200
        width: 200
        color: "red"
        anchors.centerIn: parent

        Text {
            text: "This is a test"
            anchors.centerIn: parent
        }
    }
}
