#pragma once

#include <QString>
#include <QPainter>

#pragma warning( disable : 4996 )

struct NumberBox
{
    int nWidth{ 100 };
    int nHeight{ 26 };
    QString nText{"0"};
    QFont nFont{ "Segoe UI", 12, -1, true };
    QPoint nPosition;
    QColor nBorderColor{ Qt::black };
    QColor nHighlightColor{ 34, 141, 255 };
    QColor nBackgroundColor{ 60, 60, 60 };
    QColor nForeGroundColor{ Qt::white };
    int nCursorPos{ 1 };
    int MaxCharacters{ 8 };

    void drawBody(QPainter* painter, NumberBox* currentNumberBox)
    {
        painter->setPen(nBorderColor);
        painter->drawRect(nPosition.x(), nPosition.y(), nWidth, nHeight);
        QColor bcol = currentNumberBox == nullptr ? nBackgroundColor : nHighlightColor;
        painter->fillRect(nPosition.x(), nPosition.y(), nWidth, nHeight, bcol);

        QFontMetrics f(nFont);
        f.width(nText);
        int y = f.height();
        painter->setPen(nForeGroundColor);
        painter->setFont(nFont);
        QString text = nText;

        if (currentNumberBox != nullptr)
        {
            text.insert(nCursorPos, '|');
        }

        if (nText.length() > MaxCharacters)
        {
            nCursorPos = nText.length();
            text.resize(MaxCharacters - 3);
            text += "..";
        }
        QPoint p = nPosition + QPoint(5, 2 * y / 3);
        painter->drawText(p, text);
    }

    void keyPress(QKeyEvent* event)
    {
        if (event->key() == Qt::Key::Key_Backspace)
        {
            if (nCursorPos > 0)
            {
                nText.remove(nCursorPos - 1, 1);
                nCursorPos--;
            }
        }
        if (event->key() == Qt::Key::Key_Left)
        {
            if (nCursorPos > 0)
            {
                nCursorPos--;
            }
        }
        if (event->key() == Qt::Key::Key_Right)
        {
            if (nCursorPos < nText.length())
            {
                nCursorPos++;
            }
        }
        if ((event->key() >= 48 && event->key() <= 57) || event->key() == 46)
        {
            nText.insert(nCursorPos, static_cast<QChar>(event->key()));
            nCursorPos++;
        }
        if (event->key() == Qt::Key::Key_Plus)
        {
            nText.insert(nCursorPos, '+');
            nCursorPos++;
        }
        if (event->key() == Qt::Key::Key_Minus)
        {
            nText.insert(nCursorPos, '-');
            nCursorPos++;
        }
    }
};
