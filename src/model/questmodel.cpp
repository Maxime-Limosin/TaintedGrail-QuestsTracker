#include "questmodel.h"
#include <QDebug>

QuestModel::QuestModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

int QuestModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : _quests.count(); // No children rows: flat list, root only
}

QVariant QuestModel::data(const QModelIndex &index, int role) const
{
    const Quest &quest = _quests.at(index.row());

    qDebug() << quest.id << quest.title << quest.description << quest.completed;

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

    case CompletedRole:
        return quest.completed;

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

    case CompletedRole:
        quest.completed = value.toBool();
        break;

    default:
        return false;
    }

    if(res)
        emit dataChanged(index, index, {role});

    return res;
}

QHash<int, QByteArray> QuestModel::roleNames() const
{
    return QHash<int, QByteArray> {
        { IdRole, "id"},
        { TitleRole, "title"},
        { DescriptionRole, "description"},
        { CompletedRole, "completed"}
    };
}

void QuestModel::addQuest(const QString &title, const QString &description)
{
    Quest quest = {
        (quint16) _quests.count(),
        title,
        description,
        false
    };

    beginInsertRows(QModelIndex(), _quests.count(), _quests.count()); // Tell QML to refresh UI
    _quests.append(quest);
    endInsertRows();
}

bool QuestModel::toggleCompleted(int row)
{
    if (row < 0 || row >= _quests.count())
        return false;

    QModelIndex idx = index(row);
    return setData(idx, !_quests.at(row).completed, CompletedRole);
}
