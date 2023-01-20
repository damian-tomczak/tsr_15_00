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

    QQuickItem* nParent{};
    Port* nTarget{};
    Port* nInput{};
    PortType nType{ PortType::INPUT };
    QColor nColor{ Qt::green };
    QPoint nPosition;
    float nRadius{ 10.f };

    QList<NumberBox> nNumberBoxes;

    QPoint getWorldPosition();
    Port* getPortNearestAtPosition(QPoint point, QObject* pParent, QQuickItem* pCurrentNode);

};