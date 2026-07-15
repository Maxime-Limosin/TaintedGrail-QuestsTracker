import QtQuick
import QtQuick.Layouts

import "theme.js" as Theme

Window {
    width: 600
    height: 1200
    visible: true

    title: "Tainted Grail - Quests Tracker"
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
            Layout.preferredHeight: 300
        }
    }
}
