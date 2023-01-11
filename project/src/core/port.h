#pragma once

#include <QList>
#include <QQuickItem>

#include "numberboxcore.hpp"

class Port
{
public:
    Port();

    enum PortType
    {
        Input,
        OutPut
    };

    QQuickItem* parent;
    Port* target;
    PortType type = PortType::Input;

    QList<NumberBox> numberBoxList;

};