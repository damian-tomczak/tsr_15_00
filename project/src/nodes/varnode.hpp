#pragma once

#include "corenode.h"

class VarNode : public CoreNode
{
    Q_OBJECT
        Q_PROPERTY(QString value READ getValue WRITE setValue)

public slots:
    void setValue(const QString value) { mNumberBoxes[0].mText = value; }
    QString getValue() const { return mNumberBoxes[0].mText; }

public:
    VarNode() : CoreNode("")
    {
        setTitle("Var");
        setHeight(120);
        setWidth(150);
        setFirstColor(QColor(Qt::green));
        setSecondColor(QColor(10, 160, 45));

        Port port
        {
            .mParent = this,
            .mType = Port::PortType::OUTPUT,
            .mColor = firstColor(),
            .mPosition = QPoint(125, 75),
        };

        NumberBox numberBox
        {
            .mPosition = QPoint(12, 62)
        };

        mNumberBoxes.push_back(std::move(numberBox));

        port.mNumberBoxes.push_back(std::move(numberBox));

        mOutputPorts.push_back(std::move(port));
    }

private:
};
