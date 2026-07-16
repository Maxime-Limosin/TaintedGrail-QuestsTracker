#pragma once

#include <QAbstractListModel>
#include <QList>
#include <QQmlEngine>

#include "quest.h"

class QuestModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    // Roles exposed to QML
    enum QuestRoles {
        IdRole = Qt::UserRole + 1,
        TitleRole,
        DescriptionRole,
        FinishedRole,
        ColorRole,
        SubTasksRole
    };

    explicit QuestModel(QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addQuest(const QString &title, const QString &description, QColor color = Qt::white);
    Q_INVOKABLE bool addSubTask(quint16 questId, const QString &taskDesc);
    Q_INVOKABLE bool toggleCompleted(int row);

private:
    QList<Quest> _quests;

    void printQuests();
};

