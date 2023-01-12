#include "blackboard.h"

void BlackBoard::zoom(float amount)
{

    mSquareDimension = static_cast<int>(amount * DEFAULT_SQUARE_DIMENSION);
    zoomNodes();
    update();
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

    painter->fillRect(0, 0, width, height, QBrush(mBackgroundColor));

    int verticalLines = width / mSquareDimension + 1;
    int horizontalLines = height / mSquareDimension + 1;

    painter->drawRect(0, 0, width, height);

    for (int i = -mSquareDimension; i < verticalLines; i++)
    {
        if (i % mSquareNumber == 0)
        {
            painter->setPen(QPen(mLargeLineColor, 2.5));
        }
        else
        {
            painter->setPen(QPen(mSmallLineColor, 1));
        }

        painter->drawLine(i * mSquareDimension, 0,
            i * mSquareDimension,
            height);
    }

    for (int i = -mSquareDimension; i < horizontalLines; i++)
    {
        if (i % mSquareNumber == 0)
        {
            painter->setPen(QPen(mLargeLineColor, 2.5));
        }
        else
        {
            painter->setPen(QPen(mSmallLineColor, 1));
        }

        painter->drawLine(0, i * mSquareDimension,
            width, i * mSquareDimension);
    }
}

void BlackBoard::mousePressEvent(QMouseEvent* event)
{
    mIsMouseDown = true;
    mMouseDownPosition = event->pos();
    setFocus(true);

    if (event->button() == Qt::RightButton)
    {
        mIsRighClicked = true;
        emit onRightMouseClickChanged(true);
    }
    else
    {
        mIsRighClicked = false;
        emit onRightMouseClickChanged(false);
    }
}

void BlackBoard::mouseReleaseEvent(QMouseEvent*)
{
    mIsMouseDown = false;
    mMouseDownPosition = QPoint(0, 0);
}

void BlackBoard::zoomNodes()
{
    QObjectList allc = children();
    for (int i = 0; i < allc.length(); i++)
    {
        QQuickItem* c = dynamic_cast<QQuickItem*>(allc[i]);
        if (c != nullptr)
        {
            c->setScale(static_cast<qreal>(curZoom));
        }
    }
}