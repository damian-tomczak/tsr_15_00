#pragma once

#include "corenode.h"

class SubtractNode : public CoreNode
{
public:
    SubtractNode() : CoreNode("subtract")
    {
        setTitle("Subtract");
        setHeight(180);
        setWidth(150);
        setFirstColor(QColor(7, 138, 123));
        setSecondColor(QColor(45, 53, 187));

        Port p1
        {
            .nParent = this,
            .nColor = firstColor(),
            .nPosition = QPoint(20, 80),
        };

        Port p2
        {
            .nParent = this,
            .nColor = firstColor(),
            .nPosition = QPoint(20, 130),
        };

        nInputPorts.push_back(std::move(p1));
        nInputPorts.push_back(std::move(p2));

        Port p3
        {
            .nParent = this,
            .nType = Port::PortType::OUTPUT,
            .nColor = secondColor(),
            .nPosition = QPoint(125, 105),
        };

        nOutputPorts.push_back(std::move(p3));

        Label l1
        {
            .nText = "A",
            .nPos = QPoint(40, 90),
        };

        Label l2
        {
            .nText = "B",
            .nPos = QPoint(40, 140),
        };

        nLabels.push_back(std::move(l1));
        nLabels.push_back(std::move(l2));
    }
};