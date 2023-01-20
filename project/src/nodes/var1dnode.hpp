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
            .nParent = this,
            .nType = Port::PortType::OUTPUT,
            .nColor = firstColor(),
            .nPosition = QPoint(125, 75),
        };

        NumberBox n
        {
            .nPosition = QPoint(12, 62)
        };

        nNumberBoxes.push_back(std::move(n));

        p.nNumberBoxes.push_back(std::move(n));

        nOutputPorts.push_back(std::move(p));
    }

};
