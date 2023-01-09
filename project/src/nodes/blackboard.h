#pragma once

#include <QtQuick/QQuickPaintedItem>

class BlackBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    BlackBoard();

protected:
    void paint(QPainter*) override;

signals:

public slots:

private:

};
