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

    void keyPress(QKeyEvent* event)
    {
        if (event->key() == Qt::Key::Key_Backspace)
        {
            if (mCursorPos > 0)
            {
                mText.remove(mCursorPos - 1, 1);
                mCursorPos--;
            }
        }
        if (event->key() == Qt::Key::Key_Left)
        {
            if (mCursorPos > 0)
            {
                mCursorPos--;
            }
        }
        if (event->key() == Qt::Key::Key_Right)
        {
            if (mCursorPos < mText.length())
            {
                mCursorPos++;
            }
        }
        if ((event->key() >= 48 && event->key() <= 57) || event->key() == 46)
        {
            mText.insert(mCursorPos, static_cast<QChar>(event->key()));
            mCursorPos++;
        }
        if (event->key() == Qt::Key::Key_Plus)
        {
            mText.insert(mCursorPos, '+');
            mCursorPos++;
        }
        if (event->key() == Qt::Key::Key_Minus)
        {
            mText.insert(mCursorPos, '-');
            mCursorPos++;
        }
    }
};
