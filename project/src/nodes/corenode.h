#pragma once

#include <QtQuick/QQuickPaintedItem>

#include "core/numberboxcore.hpp"
#include "core/port.h"

class CoreNode : public QQuickPaintedItem
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