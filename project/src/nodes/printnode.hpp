#pragma once

#include "corenode.h"

class PrintNode : public CoreNode
{
public:
    PrintNode() : CoreNode("print")
    {
        setTitle("Print");
        setHeight(120);
        setWidth(150);
        setFirstColor(QColor(165, 42, 42));
        setSecondColor(QColor(Qt::yellow));

        Port p
        {
            .nParent = this,
            .nColor = secondColor(),
            .nPosition = QPoint(20, 70),
        };
        nInputPorts.push_back(std::move(p));
    }

};
