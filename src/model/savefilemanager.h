#pragma once

#include <QObject>
#include <QList>
#include <QJsonObject>

#include "quest.h"

class SaveFileManager : public QObject
{
    Q_OBJECT

public:
    explicit SaveFileManager(QObject *parent = nullptr);

    QString saveFilePath();
    void saveQuestModel(const QList<Quest> &q);
    QList<Quest> loadQuestModel();

private:
    QJsonObject questToJson(const Quest &q);
    QJsonObject taskToJson(const SubTask &t);

    Quest questFromJson(const QJsonObject &obj);
    SubTask taskFromJson(const QJsonObject &obj);
};

