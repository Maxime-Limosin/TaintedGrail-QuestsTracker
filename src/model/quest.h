#pragma once

#include <QString>
#include <QColor>
#include <QList>

#include "subtask.h"

struct Quest {
    quint16 id = 0;
    bool finished = false;
    QColor color = Qt::white;

    QString title = "";
    QString description = "";
    QList<SubTask> subtasks = {};
};
