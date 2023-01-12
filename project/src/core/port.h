#pragma once

#include <QList>
#include <QQuickItem>

#include "numberboxcore.hpp"

class Port
{
public:
    enum class PortType
    {
        INPUT,
        OUTPUT
    };

    QQuickItem* mParent{};
    Port* mTarget{};
    PortType mType{ PortType::INPUT };
    QColor mColor{ Qt::green };
    QPoint mPosition;

    QList<NumberBox> mNumberBoxes;

};