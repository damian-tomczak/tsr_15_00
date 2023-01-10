#include "blackboard.h"

BlackBoard::BlackBoard()
{
}

bool BlackBoard::rightClicked() const
{
    return righClicked;
}

void BlackBoard::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setPen(Qt::black);
    drawGridLines(painter);
}

void BlackBoard::drawGridLines(QPainter* painter)
{
    int width = static_cast<int>(this->width());
    int height = static_cast<int>(this->height());

    painter->fillRect(0, 0, width, height, QBrush(backgroundColor));

    int vertLines = width / squareDimension + 1;
    int horizLines = height / squareDimension + 1;

    painter->drawRect(0, 0, width, height);

    for (int i = -squareDimension; i < vertLines; i++)
    {
        if (i % squareNumber == 0)
        {
            painter->setPen(QPen(largeLineColor, 2.5));
        }
        else
        {
            painter->setPen(QPen(smallLineColor, 1));
        }

        painter->drawLine(i * squareDimension, 0,
            i * squareDimension,
            height);
    }

    for (int i = -squareDimension; i < horizLines; i++)
    {
        if (i % squareNumber == 0)
        {
            painter->setPen(QPen(largeLineColor, 2.5));
        }
        else
        {
            painter->setPen(QPen(smallLineColor, 1));
        }

        painter->drawLine(0, i * squareDimension,
            width, i * squareDimension);
    }
}
