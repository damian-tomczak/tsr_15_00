#pragma once

#include <QtQuick/QQuickPaintedItem>
#include <QPainter>

class BlackBoard : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(bool rightClicked READ rightClicked NOTIFY onRightMouseClickChanged)

public:
    BlackBoard();
    bool rightClicked() const;

protected:
    void paint(QPainter* painter) override;

signals:
    void onRightMouseClickChanged(const bool&);

public slots:

private:
    QColor backgroundColor = QColor(50, 50, 50);
    QColor smallLineColor = QColor(38, 38, 38);
    QColor largeLineColor = QColor(28, 28, 28);

    int squareDimension = 25;
    int squareNumber = 5;

    void drawGridLines(QPainter* painter);

    bool righClicked;
};
