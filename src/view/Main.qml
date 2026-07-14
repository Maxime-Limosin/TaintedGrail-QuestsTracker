import QtQuick
import QtQuick.Layouts

import "theme.js" as Theme

Window {
    width: 640
    height: 480
    visible: true

    title: qsTr("Hello World")
    color: Theme.appBackground

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        QuestsTracker {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        QuestsMap {
            Layout.fillWidth: true
            Layout.preferredHeight: 150
        }
    }
}
