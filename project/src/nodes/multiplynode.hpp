#pragma once

#include "corenode.h"

class MultiplyNode : public CoreNode
{
public:
    MultiplyNode() : CoreNode("multiply")
    {
        setTitle("Multiply");
        setHeight(180);
        setWidth(150);
        setFirstColor(QColor(142, 68, 173));
        setSecondColor(QColor(86, 101, 115));

        Port p1
        {
            .mParent = this,
            .mColor = firstColor(),
            .mPosition = QPoint(20, 80),
        };

        Port p2
        {
            .mParent = this,
            .mColor = firstColor(),
            .mPosition = QPoint(20, 130),
        };

        mInputPorts.push_back(std::move(p1));
        mInputPorts.push_back(std::move(p2));

        Port p3
        {
            .mParent = this,
            .mType = Port::PortType::OUTPUT,
            .mColor = secondColor(),
            .mPosition = QPoint(125, 105),
        };

        mOutputPorts.push_back(std::move(p3));

        Label l1
        {
            .mText = "A",
            .mPos = QPoint(40, 90),
        };

        Label l2
        {
            .mText = "B",
            .mPos = QPoint(40, 140),
        };

        mLabels.push_back(std::move(l1));
        mLabels.push_back(std::move(l2));
    }
};