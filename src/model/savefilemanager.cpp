#include "savefilemanager.h"

#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include <QJsonArray>
#include <QJsonDocument>

SaveFileManager::SaveFileManager(QObject *parent)
    : QObject{parent}
{}

QString SaveFileManager::saveFilePath()
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation); // AppDataLocation resolves correctly on both Windows and Android
    QDir().mkpath(dir); // Ensure the directory exists before writing

    return dir + "/tg_qt_save.json";
}

void SaveFileManager::saveQuestModel(const QList<Quest> &q)
{
    QJsonObject jsonRoot;
    QJsonArray questsToSave;

    foreach(const Quest &q, q)
        questsToSave.append(questToJson(q));

    jsonRoot["quests"] = questsToSave;

    QFile saveFile = QFile(saveFilePath());
    saveFile.open(QIODevice::WriteOnly); // QFile auto
    saveFile.write(QJsonDocument(jsonRoot).toJson());
    saveFile.close();
}

QList<Quest> SaveFileManager::loadQuestModel()
{
    QFile saveFile = QFile(saveFilePath());
    QList<Quest> quests;

    if (!saveFile.open(QIODevice::ReadOnly))
        return {};

    QByteArray saveData = saveFile.readAll();
    saveFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(saveData);
    QJsonObject jsonRoot = doc.object();

    if(!jsonRoot["quests"].isArray())
        return {};

    QJsonArray jsonQuests = jsonRoot["quests"].toArray();
    quests.reserve(jsonQuests.count());

    foreach (const QJsonValue &val, jsonQuests)
    {
        QJsonObject obj = val.toObject();
        quests.append(questFromJson(obj));
    }

    return quests;
}

QJsonObject SaveFileManager::questToJson(const Quest &q)
{
    QJsonObject jsonObject;
    jsonObject["id"] = q.id;
    jsonObject["finished"] = q.finished;
    jsonObject["titl"] = q.title;
    jsonObject["description"] = q.description;

    QJsonObject colorObject;
    colorObject["r"] = q.color.red();
    colorObject["g"] = q.color.green();
    colorObject["b"] = q.color.blue();

    QJsonArray tasksObject;
    foreach(const SubTask &t, q.subtasks)
        tasksObject.append(taskToJson(t));

    jsonObject["color"] = colorObject;
    jsonObject["subtasks"] = tasksObject;
    return jsonObject;
}

QJsonObject SaveFileManager::taskToJson(const SubTask &t)
{
    QJsonObject jsonObject;
    jsonObject["id"] = t.id;
    jsonObject["completed"] = t.completed;
    jsonObject["task"] = t.task;

    return jsonObject;
}

Quest SaveFileManager::questFromJson(const QJsonObject &obj)
{
    Quest q;
    q.id = obj["id"].toInt();
    q.finished = obj["finished"].toBool();
    q.title = obj["title"].toString("");
    q.description = obj["description"].toString("");

    QJsonValue colorObj = obj["color"];
    QColor color = QColor(
        colorObj["r"].toInt(),
        colorObj["g"].toInt(),
        colorObj["b"].toInt());
    q.color = color;

    QJsonArray taskObj = obj["subtasks"].toArray();
    foreach (const QJsonValue &val, taskObj)
        q.subtasks.append(taskFromJson(val.toObject()));

    return q;
}

SubTask SaveFileManager::taskFromJson(const QJsonObject &obj)
{
    return SubTask {
        (quint8) obj["id"].toInt(0),
        obj["completed"].toBool(false),
        obj["task"].toString("")
    };
}
