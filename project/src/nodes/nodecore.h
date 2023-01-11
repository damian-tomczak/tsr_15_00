#pragma once

#include <QtQuick/QQuickPaintedItem>

class NodeCore : public QQuickPaintedItem
{
    Q_OBJECT

public:
    QList<Port> outputPort;

protected:
    void paint(QPainter*) override;
};