#pragma once

#include <QString>
#include <QPainter>

#pragma warning( disable : 4996 )

struct NumberBox
{
    int mWidth{ 100 };
    int mHeight{ 26 };
    QString mText{"0"};
    QFont mFont{ "Segoe UI", 12, -1, true };
    QPoint mPosition;
    QColor mBorderColor{ Qt::black };
    QColor mHighlightColor{ 34, 141, 255 };
    QColor mBackgroundColor{ 60, 60, 60 };
    QColor mForeGroundColor{ Qt::white };
    int mCursorPos{ 0 };
    int MaxCharacters{ 8 };

    void drawBody(QPainter* painter, NumberBox* currentNumberBox)
    {
        painter->setPen(mBorderColor);
        painter->drawRect(mPosition.x(), mPosition.y(), mWidth, mHeight);
        QColor bcol = currentNumberBox == nullptr ? mBackgroundColor : mHighlightColor;
        painter->fillRect(mPosition.x(), mPosition.y(), mWidth, mHeight, bcol);

        QFontMetrics f(mFont);
        f.width(mText);
        int y = f.height();
        painter->setPen(mForeGroundColor);
        painter->setFont(mFont);
        QString text = mText;

        if (currentNumberBox != nullptr)
        {
            text.insert(mCursorPos, '|');
        }

        if (mText.length() > MaxCharacters)
        {
            mCursorPos = mText.length();
            text.resize(MaxCharacters - 3);
            text += "..";
        }
        QPoint p = mPosition + QPoint(5, 2 * y / 3);
        painter->drawText(p, text);
    }
};
