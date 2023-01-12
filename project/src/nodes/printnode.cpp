#include "printnode.h"

PrintNode::PrintNode() : CoreNode("print")
{
    setTitle("Print");
    setHeight(120);
    setWidth(150);
    setFirstColor(QColor(165, 42, 42));
    setSecondColor(QColor(Qt::yellow));

    Port p
    {
        .mParent = this,
        .mColor = secondColor(),
        .mPosition = QPoint(20, 70),
    };
    mInputPorts.push_back(std::move(p));
}
