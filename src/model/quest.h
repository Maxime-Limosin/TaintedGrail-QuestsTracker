#pragma once

#include <QString>

struct Quest {
    quint16 id = 0;
    QString title = "";
    QString description = "";
    bool completed = false;
};
