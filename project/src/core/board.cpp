#include "board.h"

#pragma warning( disable : 4996 )

void Board::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setPen(Qt::black);
    drawGridLines(painter);
}

void Board::drawGridLines(QPainter* painter)
{
    int w = static_cast<int>(this->width());
    int h = static_cast<int>(this->height());

    painter->fillRect(0, 0, w, h, QBrush(mBackgroundColor));

    int vertLines = w / mSquareDimension + 1;
    int horizLines = h / mSquareDimension + 1;

    painter->drawRect(0, 0, w, h);

    for (int i = -mSquareDimension; i < vertLines; i++)
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
            h);
    }

    for (int i = -mSquareDimension; i < horizLines; i++)
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
            w, i * mSquareDimension);
    }
}

void Board::mousePressEvent(QMouseEvent* event)
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

void Board::mouseReleaseEvent(QMouseEvent*)
{
    mIsMouseDown = false;
    mMouseDownPosition = QPoint(0, 0);
}

void Board::wheelEvent(QWheelEvent* event)
{
    zoomAmountModifier(event->delta());
}

void Board::zoomAmountModifier(int amt)
{
    if (amt > 0)
    {
        if (mCurZoom + 0.05f < MAX_ZOOM)
        {
            mCurZoom += 0.05f;
        }
    }
    else
    {
        if (mCurZoom - 0.05f > MIN_ZOOM)
        {
            mCurZoom -= 0.05f;
        }
    }
    zoom(mCurZoom);
}

void Board::zoom(float amt)
{

    mSquareDimension = static_cast<int>(amt * DEFAULT_SQUARE_DIMENSION);
    zoomNodes();
    update();
}

void Board::zoomNodes()
{
    QObjectList allc = children();
    for (int i = 0; i < allc.length(); i++)
    {
        QQuickItem* c = dynamic_cast<QQuickItem*>(allc[i]);
        if (c != nullptr)
        {
            c->setScale(static_cast<qreal>(mCurZoom));
        }
    }
}