#pragma once

#include <QString>

struct SubTask {
    quint8 id = 0;
    bool completed = false;
    QString task = "";
};
