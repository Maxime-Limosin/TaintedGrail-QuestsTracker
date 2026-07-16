#include "questmodel.h"

#include <QDebug>
#include <QtGlobal>

QuestModel::QuestModel(QObject *parent)
    : QAbstractListModel{parent}
{
    _quests = _saveFileManager.loadQuestModel();
}

int QuestModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : _quests.count(); // No children rows: flat list, root only
}

QVariant QuestModel::data(const QModelIndex &index, int role) const
{
    const Quest &quest = _quests.at(index.row());
    QVariantList subtasksList;

    if(!index.isValid() || index.row() >= _quests.count())
        return {};

    switch(role)
    {
    case IdRole:
        return quest.id;

    case TitleRole:
        return quest.title;

    case DescriptionRole:
        return quest.description;

    case FinishedRole:
        return quest.finished;

    case ColorRole:
        return quest.color;

    case SubTasksRole:
        for(const SubTask &subtask : quest.subtasks)
        {
            QVariantMap subtaskMap;
            subtaskMap["id"] = subtask.id;
            subtaskMap["completed"] = subtask.completed;
            subtaskMap["task"] = subtask.task;
            subtasksList.append(subtaskMap);
        }
        return subtasksList;

    default:
        return {};
    }
}

bool QuestModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Quest &quest = _quests[index.row()];
    bool res = true;

    if(!index.isValid() || index.row() >= _quests.count())
        return false;

    switch(role)
    {
    case IdRole:
        quest.id = value.toInt(&res);
        break;

    case TitleRole:
        quest.title = value.toString();
        break;

    case DescriptionRole:
        quest.description = value.toString();
        break;

    case FinishedRole:
        quest.finished = value.toBool();
        break;

    case ColorRole:
        qDebug() << "Set color" <<  value;
        break;

    case SubTasksRole:
        qDebug() << "Set subtask" <<  value;
        break;

    default:
        return false;
    }

    if(res)
        emit dataChanged(index, index, {role});

    saveQuestModel();
    return res;
}

QHash<int, QByteArray> QuestModel::roleNames() const
{
    return QHash<int, QByteArray> {
        { IdRole, "id"},
        { TitleRole, "title"},
        { DescriptionRole, "description"},
        { FinishedRole, "finished"},
        { ColorRole, "color"},
        { SubTasksRole, "subtasks"}
    };
}

void QuestModel::addQuest(const QString &title, const QString &description, QColor color)
{
    if(color == Qt::white) // If it's default color
        color = QColor(rand() % 256, rand() % 256, rand() % 256);

    Quest quest = {
        (quint16) _quests.count(),
        false,
        color,
        title,
        description,
        {}
    };

    beginInsertRows(QModelIndex(), _quests.count(), _quests.count()); // Tell QML to refresh UI
    _quests.append(quest);
    endInsertRows();

    saveQuestModel();
}

bool QuestModel::addSubTask(quint16 questId, const QString &taskDesc)
{
    int row = findQuestRowById(questId);
    if(row == -1)
        return false;

    // Create and add SubTask
    Quest &quest = _quests[row];

    SubTask task = {
        (quint8) quest.subtasks.count(),
        false,
        taskDesc
    };

    quest.subtasks.append(task);

    // Refresh UI
    QModelIndex idx = index(row);
    emit dataChanged(idx, idx, {SubTasksRole});
    saveQuestModel();
    return true;
}

bool QuestModel::toggleFinished(int row)
{
    if (row < 0 || row >= _quests.count())
        return false;

    QModelIndex idx = index(row);
    return setData(idx, !_quests.at(row).finished, FinishedRole);
}

bool QuestModel::toggleSubTaskCompleted(quint16 questId, quint8 taskId)
{
    int questRow = findQuestRowById(questId);
    if(questRow == -1)
        return false;

    Quest &quest = _quests[questRow];
    int taskRow = findSubTaskRowById(quest, taskId);
    if(taskRow == -1)
        return false;

    SubTask &task = quest.subtasks[taskRow];
    task.completed = !task.completed;

    saveQuestModel();
    return true;
}

// Return -1 if row was not found
int QuestModel::findQuestRowById(quint16 questId)
{
    int row = -1;

    // Find quest row
    for(int i = 0; i < _quests.count(); i++)
        if(_quests.at(i).id == questId)
        {
            row = i;
            break;
        }

    return row;
}

// Return -1 if row was not found
int QuestModel::findSubTaskRowById(const Quest &quest, quint8 taskId)
{
    int row = -1;

    // Find task row
    for(int i = 0; i < quest.subtasks.count(); i++)
        if(quest.subtasks.at(i).id == taskId)
        {
            row = i;
            break;
        }

    return row;
}

void QuestModel::saveQuestModel()
{
    _saveFileManager.saveQuestModel(_quests);
}

// For debug purposes
void QuestModel::printQuests()
{
    foreach(const Quest &q, _quests)
    {
        qDebug() << "Id:" << q.id;
        qDebug() << "finished:" << q.finished;
        qDebug() << "title:" << q.title;
        qDebug() << "desc:" << q.description;

        qDebug() << "tasks:";
        foreach(const SubTask &t, q.subtasks)
            qDebug() << " " << t.id << t.completed << t.task;

        qDebug() << "";
    }
}
