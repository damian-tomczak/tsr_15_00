#include "corenode.h"

#pragma warning( disable : 4996 )

inline QPoint convertQPoint(const QPointF& fPoint)
{
    return QPoint(static_cast<int>(fPoint.x()), static_cast<int>(fPoint.y()));
}

QString CoreNode::resultString()
{
    QString result = mFunctionName;
    for (int j{}; j < mOutputPorts.length(); j++)
    {
        if (mpNumberBox != nullptr)
        {
            result += mpNumberBox->mText;
        }
    }

    if (mInputPorts.length() != 0)
    {
        result += "(";
    }

    for (int i{}; i < mInputPorts.length(); i++)
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
    for (int i{}; i < mInputPorts.length(); i++)
    {
        pPainter->setBrush(mInputPorts[i].mColor);
        int r = static_cast<int>(mInputPorts[i].mRadius);
        pPainter->drawEllipse(mInputPorts[i].mPosition, r, r);
    }
    for (int i{}; i < mOutputPorts.length(); i++)
    {
        pPainter->setBrush(mOutputPorts[i].mColor);
        int r = static_cast<int>(mOutputPorts[i].mRadius);
        pPainter->drawEllipse(mOutputPorts[i].mPosition, r, r);
    }
}

void CoreNode::drawLabels(QPainter* pPainter)
{
    for (int i{}; i < mLabels.length(); i++)
    {
        mLabels[i].drawBody(pPainter);
    }
}

void CoreNode::drawNumberBox(QPainter* pPainter)
{
    if (mpNumberBox != nullptr)
    {
        mpNumberBox->drawBody(pPainter);
    }
}

void CoreNode::paint(QPainter* pPainter)
{
    drawBody(pPainter);
    drawTitle(pPainter);
    drawPorts(pPainter);
    drawLabels(pPainter);
    drawNumberBox(pPainter);
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
    forceActiveFocus();
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
    if (pEvent->lostFocus() && (mpNumberBox != nullptr))
    {
        mpNumberBox->mIsFocused = false;
        update();
    }
}

void CoreNode::keyPressEvent(QKeyEvent* pEvent)
{
    if (mIsEditable && (mpNumberBox != nullptr))
    {
        mpNumberBox->keyPress(pEvent);
        update();
    }
    if (mIsDestructible && (pEvent->key() == Qt::Key::Key_Delete))
    {
        for (int i{}; i < mOutputPorts.length(); i++)
        {
            Port* pPort = mOutputPorts[i].mInput;
            if (pPort != nullptr)
            {
                pPort->mTarget = nullptr;
            }
        }
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
    if ((mpNumberBox != nullptr))
    {
        if (mIsEditable && isClickedNumberBox(point))
        {
            mpNumberBox->mIsFocused = true;
        }
        else
        {
            mpNumberBox->mIsFocused = false;
        }
    }
    update();
}

bool CoreNode::isClickedNumberBox(const QPoint& point)
{
    if (abs(point.x() - mpNumberBox->mPosition.x()) <= mpNumberBox->mWidth)
    {
        if (abs(point.y() - mpNumberBox->mPosition.y()) <= mpNumberBox->mHeight)
        {
            return true;
        }
    }
    return false;
}

Port* CoreNode::getClickedPort(const QPoint& point)
{
    Port* pPort{};

    for (int i{}; i < mOutputPorts.length(); i++)
    {
        if (abs(point.x() - mOutputPorts[i].mPosition.x()) <= mOutputPorts[i].mRadius)
        {
            if (abs(point.y() - mOutputPorts[i].mPosition.y()) <= mOutputPorts[i].mRadius)
            {
                pPort = &mOutputPorts[i];
            }
        }
    }
    for (int i{}; i < mInputPorts.length(); i++)
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
    else if (mCurrentPort->mInput != nullptr)
    {
        mCurrentPort->mInput->mTarget = nullptr;
    }
}