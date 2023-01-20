#include "board.h"
#include "nodes/corenode.h"

#pragma warning( disable : 4996 )

void Board::paint(QPainter* painter)
{
    painter->setRenderHints(QPainter::Antialiasing, true);
    painter->setPen(Qt::black);
    drawGridLines(painter);
    drawConnectors(painter);
    drawCurrentLines(painter);
}

void Board::drawGridLines(QPainter* painter)
{
    int w = static_cast<int>(this->width());
    int h = static_cast<int>(this->height());

    painter->fillRect(0, 0, w, h, QBrush(mBackgroundColor));
    
    int horizLines = h / mSquareDimension + 1;
    int vertLines = w / mSquareDimension + 1;

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

        painter->drawLine(i * mSquareDimension, 
            0,
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

        painter->drawLine(0, 
            i * mSquareDimension,
            w, 
            i * mSquareDimension);
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
    QObjectList children = this->children();
    for (int i = 0; i < children.length(); i++)
    {
        QQuickItem* pChild = dynamic_cast<QQuickItem*>(children[i]);
        if (pChild != nullptr)
        {
            pChild->setScale(static_cast<qreal>(mCurZoom));
        }
    }
}

void Board::drawCurrentLines(QPainter* pPainter)
{
    if (mIsDrawCurrentLine)
    {
        if (mCurrentPortType == Port::PortType::OUTPUT)
        {
            QPoint port1 = mFromCurrentLine;
            QPoint port2 = mToCurrentLine;

            pPainter->setPen(QPen(mCurrentLineColor, 5));
            pPainter->drawLine(port1.x(), port1.y(), port1.x() + 40, port1.y());
            pPainter->drawLine(port1.x() + 40, port1.y(), port2.x() - 40, port2.y());
            pPainter->drawLine(port2.x() - 40, port2.y(), port2.x(), port2.y());
        }
        else
        {
            QPoint port1 = mFromCurrentLine;
            QPoint port2 = mToCurrentLine;

            pPainter->setPen(QPen(mCurrentLineColor, 5));
            pPainter->drawLine(port1.x(), port1.y(), port1.x() - 40, port1.y());
            pPainter->drawLine(port1.x() - 40, port1.y(), port2.x() + 40, port2.y());
            pPainter->drawLine(port2.x() + 40, port2.y(), port2.x(), port2.y());
        }
    }
}

void Board::drawConnectors(QPainter* painter)
{
    QObjectList children = this->children();
    for (int i = 0; i < children.length(); i++)
    {
        CoreNode* pNode = dynamic_cast<CoreNode*>(children[i]);
        if (pNode != nullptr)
        {

            for (int j = 0; j < pNode->mInputPorts.length(); j++)
            {
                if (pNode->mInputPorts[j].mTarget != nullptr)
                {
                    QPoint port1 = pNode->mInputPorts[j].mTarget->getWorldPosition();
                    QPoint port2 = pNode->mInputPorts[j].getWorldPosition();

                    painter->setPen(QPen(pNode->mInputPorts[j].mColor, 5));
                    painter->drawLine(port1.x(), port1.y(), port1.x() + 40, port1.y());
                    painter->drawLine(port1.x() + 40, port1.y(), port2.x() - 40, port2.y());
                    painter->drawLine(port2.x() - 40, port2.y(), port2.x(), port2.y());
                }
            }
        }
    }
}
