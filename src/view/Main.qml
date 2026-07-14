import QtQuick
import QtQuick.Layouts

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ColumnLayout {
        anchors.fill: parent

        QuestsTracker {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        QuestsMap {
            Layout.fillWidth: true
        }
    }
}
