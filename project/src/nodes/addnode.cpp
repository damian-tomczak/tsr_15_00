#include "addnode.h"

AddNode::AddNode() : CoreNode("add")
{
    setTitle("Add");
    setHeight(180);
    setWidth(150);
    setFirstColor(QColor(7, 138, 123));
    setSecondColor(QColor(45, 53, 187));

    Port p1;
    p1.mParent = this;
    p1.mPosition = QPoint(20, 80);
    p1.mColor = firstColor();

    Port p2;
    p2.mParent = this;
    p2.mPosition = QPoint(20, 130);
    p2.mColor = firstColor();

    mInputPorts.push_back(std::move(p1));
    mInputPorts.push_back(std::move(p2));

    Port p3;
    p3.mParent = this;
    p3.mPosition = QPoint(125, 105);
    p3.mColor = secondColor();
    p3.mType = Port::PortType::OUTPUT;

    mOutputPorts.push_back(std::move(p3));

    Label l1;
    l1.mText = "A";
    l1.mPos = QPoint(40, 90);

    Label l2;
    l2.mText = "B";
    l2.mPos = QPoint(40, 140);

    mLabels.push_back(std::move(l1));
    mLabels.push_back(std::move(l2));
}
