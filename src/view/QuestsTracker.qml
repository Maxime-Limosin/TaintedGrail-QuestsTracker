import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

import "element"
import "theme.js" as Theme

ColumnLayout {
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

                TextField {
                    Layout.fillWidth: true
                    placeholderText: "Add a task..."
                    font.pointSize: 12

                    // Submit on Enter
                    onAccepted: {
                        if (text.trim().length <= 0)
                            return

                        QuestModel.addSubTask(questId, text.trim())
                        text = ""
                    }
                }
            }
        }
    }
}
