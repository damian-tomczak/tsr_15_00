#pragma once

#include<QString>
#include<QPoint>
#include<QColor>
#include<QFont>
#include<QPainter>

class Label
{
public:
    QString mText{};
    QFont mFont{ "Segoe UI", 12, -1, true };
    QPoint mPos{ 0, 0 };
    QColor mColor{ Qt::white };

    void paint(QPainter* painter)
    {
        painter->setPen(mColor);
        painter->setFont(mFont);
        painter->drawText(mPos, mText);
    }
};