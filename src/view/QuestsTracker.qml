import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import "element"
import "theme.js" as Theme

ColumnLayout {
    Component.onCompleted: {
        QuestModel.addQuest("Title 1", "Desc 1")
        QuestModel.addQuest("Title 2", "Desc 2")
        QuestModel.addQuest("Title 3", "Desc 3")

        QuestModel.addSubTask(0, "Task 1")
        QuestModel.addSubTask(0, "Task 2")

        QuestModel.addSubTask(1, "Task 1")
    }

    TGText {
        text: "Current Quests"
        font.pointSize: 18
    }

    ListView {
        id: listView
        model: QuestModel
        spacing: 15

        Layout.fillHeight: true
        Layout.fillWidth: true

        delegate: ColumnLayout {
            id: taskRoot
            property var subtasks: model.subtasks
            property int questId: model.id

            spacing: 5
            width: ListView.view.width

            RowLayout {
                Layout.fillWidth: true

                Rectangle {
                    id: questColor
                    height: 20; width: height
                    color: model.color; radius: width/2
                    Layout.alignment: Qt.AlignVCenter
                }

                TGText {
                    id: questTitle
                    text: model.title
                    font.pointSize: 16
                    Layout.alignment: Qt.AlignVCenter
                }
            }

            TGText {
                id: questDescription
                text: model.description
                color: Theme.lightGrey
                Layout.leftMargin: questColor.width
            }

            // Display each subtasks in a column
            Column {
                Layout.leftMargin: questColor.width

                Repeater {
                    model: taskRoot.subtasks

                    RowLayout {

                        CheckBox {
                            checked: modelData.completed
                            onClicked: QuestModel.toggleSubTaskCompleted(questId, modelData.id)
                            Layout.alignment: Qt.AlignVCenter
                        }

                        TGText {
                            text: modelData.task
                            Layout.alignment: Qt.AlignVCenter
                            Layout.leftMargin: -10 // Material style Checkbox has a lot a padding by default
                        }
                    }
                }
            }
        }
    }
}
