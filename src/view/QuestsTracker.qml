import QtQuick
import QtQuick.Layouts

import "element"
import "theme.js" as Theme

ColumnLayout {
    Component.onCompleted: {
        QuestModel.addQuest("Title 1", "Desc 1")
        QuestModel.addQuest("Title 2", "Desc 2")
    }

    TGText {
        text: "Current Quests"
        font.pointSize: 18
    }

    ListView {
        model: QuestModel

        Layout.fillHeight: true
        Layout.fillWidth: true

        delegate: RowLayout {
            width: ListView.view.width

            TGText { text: model.title }
            TGText { text: model.description }
        }
    }
}
