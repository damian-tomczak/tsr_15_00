#pragma once

#include <QList>
#include <QQuickItem>

#include "numberboxcore.hpp"

struct Port
{
    enum class PortType
    {
        INPUT,
        OUTPUT
    };

    QQuickItem* mParent{};
    Port* mTarget{};
    Port* mInput{};
    PortType mType{ PortType::INPUT };
    QColor mColor{ Qt::green };
    QPoint mPosition;
    float mRadius{ 10.f };

    QList<NumberBox> mNumberBoxes;

    QPoint getWorldPosition();

};