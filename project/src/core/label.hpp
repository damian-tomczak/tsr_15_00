#pragma once

#include<QString>
#include<QPoint>
#include<QColor>
#include<QFont>
#include<QPainter>

class Label
{
public:
    QString nText{};
    QFont nFont{ "Segoe UI", 12, -1, true };
    QPoint nPos{ 0, 0 };
    QColor nColor{ Qt::white };

    void paint(QPainter* painter)
    {
        painter->setPen(nColor);
        painter->setFont(nFont);
        painter->drawText(nPos, nText);
    }

    void drawBody(QPainter* painter)
    {
        painter->setPen(nColor);
        painter->setFont(nFont);
        painter->drawText(nPos, nText);
    }
};