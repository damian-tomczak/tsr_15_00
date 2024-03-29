#pragma once

#include <QList>
#include <QQuickItem>

#include "numberbox.hpp"

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

    QPoint getWorldPosition();
    Port* getPortNearestAtPosition(QPoint point, QObject* pParent, QQuickItem* pCurrentNode);

};