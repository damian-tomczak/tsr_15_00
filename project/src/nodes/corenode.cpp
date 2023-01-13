#include "corenode.h"

#pragma warning( disable : 4996 )

inline QPoint convertQPoint(const QPointF& fPoint)
{
    return QPoint(static_cast<int>(fPoint.x()), static_cast<int>(fPoint.y()));
}

QString CoreNode::resultString()
{
    QString result = mFunctionName;
    for (int j = 0; j < mOutputPorts.length(); j++)
    {
        for (int k = 0; k < mOutputPorts[j].mNumberBoxes.length(); k++)
        {
            for (int l = 0; l < mNumberBoxes.length(); l++)
            {
                result += mNumberBoxes[l].mText + "";
            }
        }
    }

    if (mInputPorts.length() != 0)
    {
        result += "(";
    }

    for (int i = 0; i < mInputPorts.length(); i++)
    {
        Port* port = mInputPorts[i].mTarget;
        if (port == nullptr)
        {
            continue;
        }

        result += dynamic_cast<CoreNode*>(mInputPorts[i].mTarget->mParent)->resultString();
        if (i != mInputPorts.length() - 1)
        {
            result += ",";
        }
    }

    if (mInputPorts.length() != 0)
    {
        result += ")";
    }

    return result;
}

QColor CoreNode::firstColor() const
{
    return mFirstColor;
}
QColor CoreNode::secondColor() const
{
    return mSecondColor;
}

void CoreNode::setTitle(const QString title)
{
    if (title == mTitle)
    {
        return;
    }
    else
    {
        mTitle = title;
        update();
    }
}

void CoreNode::setFirstColor(const QColor color)
{
    if (color == mFirstColor)
    {
        return;
    }
    else
    {
        mFirstColor = color;
        update();
    }
}

void CoreNode::setSecondColor(const QColor color)
{
    if (color == mSecondColor)
    {
        return;
    }
    else
    {
        mSecondColor = color;
        update();
    }
}

void CoreNode::drawBody(QPainter* pPainter)
{
    int w = static_cast<int>(width());
    int h = static_cast<int>(height());

    pPainter->fillRect(0, 0, w, h, QBrush(mBackgroundColor));

    QLinearGradient g(QPoint(0, 0), QPoint(w, mPanelHeight));
    g.setColorAt(0, mFirstColor);
    g.setColorAt(1, mSecondColor);
    pPainter->fillRect(0, 0, w, mPanelHeight, QBrush(g));


    pPainter->setPen(mHighlightColor);
    pPainter->drawRect(1, 1, w - 2, h - 2);
    pPainter->drawRect(1, 1, w, mPanelHeight - 2);
}

void CoreNode::drawTitle(QPainter* pPainter)
{
    pPainter->setPen(mTitleColor);
    pPainter->setFont(mTitleFont);
    QFontMetrics f(mTitleFont);
    int x = f.width(mTitle);
    int y = f.height();
    pPainter->drawText(x / 2, y, mTitle);
}

void CoreNode::drawPorts(QPainter* pPainter)
{
    pPainter->setRenderHint(QPainter::RenderHint::Antialiasing, true);
    for (int i = 0; i < mInputPorts.length(); i++)
    {
        pPainter->setBrush(mInputPorts[i].mColor);
        int r = static_cast<int>(mInputPorts[i].mRadius);
        pPainter->drawEllipse(mInputPorts[i].mPosition, r, r);
    }
    for (int i = 0; i < mOutputPorts.length(); i++)
    {
        pPainter->setBrush(mOutputPorts[i].mColor);
        int r = static_cast<int>(mOutputPorts[i].mRadius);
        pPainter->drawEllipse(mOutputPorts[i].mPosition, r, r);
    }
}

void CoreNode::drawLabels(QPainter* pPainter)
{
    for (int i = 0; i < mLabels.length(); i++)
    {
        mLabels[i].drawBody(pPainter);
    }
}

void CoreNode::drawNumberBoxes(QPainter* pPainter)
{
    for (int i = 0; i < mNumberBoxes.length(); i++)
    {
        mNumberBoxes[i].drawBody(pPainter, mpCurrentNumberBox);
    }
}

void CoreNode::paint(QPainter* pPainter)
{
    drawBody(pPainter);
    drawTitle(pPainter);
    drawPorts(pPainter);
    drawLabels(pPainter);
    drawNumberBoxes(pPainter);
}

void CoreNode::mouseMoveEvent(QMouseEvent* pEvent)
{
    if (mIsMouseClickedOnHeader)
    {
        QPoint curr = QPoint(static_cast<int>(position().x()), static_cast<int>(position().y()));
        QPoint l = curr - mLastMousePosition + pEvent->pos();
        setPosition(l);
    }
    portLineMoveHelper(pEvent->pos());
}

void CoreNode::mousePressEvent(QMouseEvent* pEvent)
{
    setFocus(true);
    mLastMousePosition = pEvent->pos();
    if (isMouseOnHeader(pEvent->pos()))
    {
        mIsMouseClickedOnHeader = true;
    }
    else
    {
        portClickHelper(pEvent->pos());
        numberBoxClickHelper(pEvent->pos());
    }
}

void CoreNode::mouseReleaseEvent(QMouseEvent* pEvent)
{
    mIsMouseClickedOnHeader = false;
    releasePortTargeter(pEvent->pos());
}

void CoreNode::focusOutEvent(QFocusEvent* pEvent)
{
    if (pEvent->lostFocus())
    {
        mpCurrentNumberBox = nullptr;
        update();
    }
}

void CoreNode::keyPressEvent(QKeyEvent* pEvent)
{
    if (mpCurrentNumberBox != nullptr)
    {
        mpCurrentNumberBox->keyPress(pEvent);
        update();
    }
    if (pEvent->key() == Qt::Key::Key_Delete)
    {
        deleteLater();
        dynamic_cast<Board*>(parent())->update();
    }
}

bool CoreNode::isMouseOnHeader(const QPoint& point)
{
    if (point.x() > 0 && point.x() <= width())
    {
        if (point.y() > 0 && point.y() <= panelHeight())
        {
            return true;
        }
    }
    return false;
}

void CoreNode::portClickHelper(const QPoint& point)
{
    Port* pPort = getClickedPort(point);
    if (pPort != nullptr)
    {
        Board* pBoard = dynamic_cast<Board*>(parent());
        pBoard->mIsDrawCurrentLine = true;
        pBoard->mCurrentPortType = pPort->mType;
        pBoard->mCurrentLineColor = pPort->mColor;
        pBoard->mFromCurrentLine = pPort->getWorldPosition();
        pBoard->mToCurrentLine = point + convertQPoint(position());
        if (pPort->mType == Port::PortType::INPUT)
        {
            mIsInputPortClicked = true;

        }
        else
        {
            mIsOutPutPortClicked = true;
        }
        mCurrentPort = pPort;
    }
}

void CoreNode::numberBoxClickHelper(const QPoint& point)
{
    NumberBox* pNumberBox = getClickedNumberBox(point);
    if (pNumberBox != nullptr)
    {
        mpCurrentNumberBox = pNumberBox;
    }
    else
    {
        mpCurrentNumberBox = nullptr;

    }
    update();
}

NumberBox* CoreNode::getClickedNumberBox(const QPoint& point)
{
    NumberBox* pPort{};

    for (int i = 0; i < mNumberBoxes.length(); i++)
    {
        if (abs(point.x() - mNumberBoxes[i].mPosition.x()) <= mNumberBoxes[i].mWidth)
        {
            if (abs(point.y() - mNumberBoxes[i].mPosition.y()) <= mNumberBoxes[i].mHeight)
            {
                pPort = &mNumberBoxes[i];
            }
        }
    }
    return pPort;
}

Port* CoreNode::getClickedPort(const QPoint& point)
{
    Port* pPort{};

    for (int i = 0; i < mOutputPorts.length(); i++)
    {
        if (abs(point.x() - mOutputPorts[i].mPosition.x()) <= mOutputPorts[i].mRadius)
        {
            if (abs(point.y() - mOutputPorts[i].mPosition.y()) <= mOutputPorts[i].mRadius)
            {
                pPort = &mOutputPorts[i];
            }
        }
    }
    for (int i = 0; i < mInputPorts.length(); i++)
    {
        if (abs(point.x() - mInputPorts[i].mPosition.x()) <= mInputPorts[i].mRadius)
        {
            if (abs(point.y() - mInputPorts[i].mPosition.y()) <= mInputPorts[i].mRadius)
            {
                pPort = &mInputPorts[i];
            }
        }
    }
    return pPort;
}

void CoreNode::portLineMoveHelper(const QPoint& point)
{
    if (mIsInputPortClicked || mIsOutPutPortClicked)
    {
        Board* pBoard = dynamic_cast<Board*>(parent());
        pBoard->mToCurrentLine = point + convertQPoint(position());
        pBoard->mFromCurrentLine = mCurrentPort->getWorldPosition();
    }
    dynamic_cast<QQuickItem*>(parent())->update();
}

void CoreNode::releasePortTargeter(const QPoint& point)
{
    Board* pBoard = dynamic_cast<Board*>(parent());
    pBoard->mIsDrawCurrentLine = false;
    pBoard->update();
    if (mIsInputPortClicked)
    {
        mIsInputPortClicked = false;
        Port* pPort{};
        pPort = pPort->getPortNearestAtPosition(point + convertQPoint(position()), parent(), this);
        if (pPort != nullptr)
        {
            if (pPort->mType == Port::PortType::OUTPUT)
            {
                bindPort(pPort, mCurrentPort);
            }
        }
        else
        {
            connectionRemover();
        }
    }
    if (mIsOutPutPortClicked)
    {
        mIsOutPutPortClicked = false;
        Port* pPort{};
        pPort = pPort->getPortNearestAtPosition(point + convertQPoint(position()), parent(), this);
        if (pPort != nullptr)
        {
            if (pPort->mType == Port::PortType::INPUT)
            {
                bindPort(mCurrentPort, pPort);
            }
        }
        else
        {
            connectionRemover();
        }
    }
    mCurrentPort = nullptr;
}

void CoreNode::connectionRemover()
{
    if (mCurrentPort == nullptr)
    {
        return;
    }
    if (mCurrentPort->mType == Port::PortType::INPUT)
    {
        mCurrentPort->mTarget = nullptr;
    }
    else
    {
        if (mCurrentPort->mInput != nullptr)
        {
            mCurrentPort->mInput->mTarget = nullptr;
        }
    }
}

void CoreNode::bindPort(Port* pPort1, Port* pPort2)
{
    pPort2->mTarget = pPort1;
    pPort1->mInput = pPort2;
}