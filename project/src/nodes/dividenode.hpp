#pragma once

#include "corenode.h"

class DivideNode : public CoreNode
{
public:
    DivideNode() : CoreNode("divide")
    {
        setTitle("Divide");
        setHeight(180);
        setWidth(150);
        setFirstColor(QColor(142, 68, 173));
        setSecondColor(QColor(86, 101, 115));

        Port port1
        {
            .mParent = this,
            .mColor = firstColor(),
            .mPosition = QPoint(20, 80),
        };

        Port port2
        {
            .mParent = this,
            .mColor = firstColor(),
            .mPosition = QPoint(20, 130),
        };

        mInputPorts.push_back(std::move(port1));
        mInputPorts.push_back(std::move(port2));

        Port port3
        {
            .mParent = this,
            .mType = Port::PortType::OUTPUT,
            .mColor = secondColor(),
            .mPosition = QPoint(125, 105),
        };

        mOutputPorts.push_back(std::move(port3));

        Label label1
        {
            .mText = "A",
            .mPos = QPoint(40, 90),
        };

        Label label2
        {
            .mText = "B",
            .mPos = QPoint(40, 140),
        };

        mLabels.push_back(std::move(label1));
        mLabels.push_back(std::move(label2));
    }
};