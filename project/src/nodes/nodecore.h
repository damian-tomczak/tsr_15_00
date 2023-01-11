#pragma once

#include <QtQuick/QQuickPaintedItem>

#include "numberboxcore.hpp"
#include "port.h"

class NodeCore : public QQuickPaintedItem
{
    Q_OBJECT

public:
    QList<Port> inputPort;
    QList<Port> outputPort;
    QList<NumberBox> numberBoxList;
    QString functionName;

    QString resultString();

protected:
    void paint(QPainter* painter) override;
};