#include "corenode.h"

#pragma warning( disable : 4996 )

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

void CoreNode::drawBody(QPainter* painter)
{
    int w = static_cast<int>(width());
    int h = static_cast<int>(height());

    painter->fillRect(0, 0, w, h, QBrush(mBackgroundColor));

    QLinearGradient g(QPoint(0, 0), QPoint(w, mPanelHeight));
    g.setColorAt(0, mFirstColor);
    g.setColorAt(1, mSecondColor);
    painter->fillRect(0, 0, w, mPanelHeight, QBrush(g));


    painter->setPen(mHighlightColor);
    painter->drawRect(1, 1, w - 2, h - 2);
    painter->drawRect(1, 1, w, mPanelHeight - 2);
}

void CoreNode::drawTitle(QPainter* painter)
{
    painter->setPen(mTitleColor);
    painter->setFont(mTitleFont);
    QFontMetrics f(mTitleFont);
    int x = f.width(mTitle);
    int y = f.height();
    painter->drawText(x / 2, y, mTitle);
}

void CoreNode::drawPorts(QPainter* painter)
{
    painter->setRenderHint(QPainter::RenderHint::Antialiasing, true);
    for (int i = 0; i < mInputPorts.length(); i++)
    {
        painter->setBrush(mInputPorts[i].mColor);
        int r = static_cast<int>(mInputPorts[i].mRadius);
        painter->drawEllipse(mInputPorts[i].mPosition, r, r);
    }
    for (int i = 0; i < mOutputPorts.length(); i++)
    {
        painter->setBrush(mOutputPorts[i].mColor);
        int r = static_cast<int>(mOutputPorts[i].mRadius);
        painter->drawEllipse(mOutputPorts[i].mPosition, r, r);
    }
}

void CoreNode::drawLabels(QPainter* painter)
{
    for (int i = 0; i < mLabels.length(); i++)
    {
        mLabels[i].drawBody(painter);
    }
}

void CoreNode::drawNumberBoxes(QPainter* painter)
{
    for (int i = 0; i < mNumberBoxes.length(); i++)
    {
        mNumberBoxes[i].drawBody(painter, mpCurrentNumberBox);
    }
}

void CoreNode::paint(QPainter* painter)
{
    drawBody(painter);
    drawTitle(painter);
    drawPorts(painter);
    drawLabels(painter);
    drawNumberBoxes(painter);
}

void CoreNode::mouseMoveEvent(QMouseEvent* event)
{
    if (mIsMouseClickedOnHeader)
    {
        QPoint curr = QPoint(static_cast<int>(position().x()), static_cast<int>(position().y()));
        QPoint l = curr - mLastMousePosition + event->pos();
        setPosition(l);
    }
}

void CoreNode::mousePressEvent(QMouseEvent* event)
{
    setFocus(true);
    mLastMousePosition = event->pos();
    if (isMouseOnHeader(event->pos()))
    {
        mIsMouseClickedOnHeader = true;
    }
}

void CoreNode::mouseReleaseEvent(QMouseEvent* event)
{
    mIsMouseClickedOnHeader = false;
}

void CoreNode::focusOutEvent(QFocusEvent* event)
{
    if (event->lostFocus())
    {
        mpCurrentNumberBox = nullptr;
        update();
    }
}

void CoreNode::keyPressEvent(QKeyEvent* event)
{
    if (mpCurrentNumberBox != nullptr)
    {
        mpCurrentNumberBox->keyPress(event);
        update();
    }
    if (event->key() == Qt::Key::Key_Delete)
    {
        deleteLater();
        parent()->update();
    }
}

bool CoreNode::isMouseOnHeader(QPoint point)
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