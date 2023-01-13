#pragma once

#include "corenode.h"

class Var1DNode : public CoreNode
{
public:
    Var1DNode() : CoreNode("")
    {
        setTitle("Var 1D");
        setHeight(120);
        setWidth(150);
        setFirstColor(QColor(Qt::green));
        setSecondColor(QColor(10, 160, 45));

        Port p
        {
            .mParent = this,
            .mType = Port::PortType::OUTPUT,
            .mColor = firstColor(),
            .mPosition = QPoint(125, 75),
        };

        NumberBox n
        {
            .mPosition = QPoint(12, 62)
        };

        mNumberBoxes.push_back(std::move(n));

        p.mNumberBoxes.push_back(std::move(n));

        mOutputPorts.push_back(std::move(p));
    }

};
