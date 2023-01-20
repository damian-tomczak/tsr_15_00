#include "corenode.h"

#pragma warning( disable : 4996 )

inline QPoint convertQPoint(const QPointF& fPoint)
{
    return QPoint(static_cast<int>(fPoint.x()), static_cast<int>(fPoint.y()));
}

QString CoreNode::resultString()
{
    QString result = nFunctionName;
    for (int j = 0; j < nOutputPorts.length(); j++)
    {
        for (int k = 0; k < nOutputPorts[j].nNumberBoxes.length(); k++)
        {
            for (int l = 0; l < nNumberBoxes.length(); l++)
            {
                result += nNumberBoxes[l].nText + "";
            }
        }
    }

    if (nInputPorts.length() != 0)
    {
        result += "(";
    }

    for (int i = 0; i < nInputPorts.length(); i++)
    {
        Port* port = nInputPorts[i].nTarget;
        if (port == nullptr)
        {
            continue;
        }

        result += dynamic_cast<CoreNode*>(nInputPorts[i].nTarget->nParent)->resultString();
        if (i != nInputPorts.length() - 1)
        {
            result += ",";
        }
    }

    if (nInputPorts.length() != 0)
    {
        result += ")";
    }

    return result;
}

QColor CoreNode::firstColor() const
{
    return nFirstColor;
}
QColor CoreNode::secondColor() const
{
    return nSecondColor;
}

void CoreNode::setTitle(const QString title)
{
    if (title == nTitle)
    {
        return;
    }
    else
    {
        nTitle = title;
        update();
    }
}

void CoreNode::setFirstColor(const QColor color)
{
    if (color == nFirstColor)
    {
        return;
    }
    else
    {
        nFirstColor = color;
        update();
    }
}

void CoreNode::setSecondColor(const QColor color)
{
    if (color == nSecondColor)
    {
        return;
    }
    else
    {
        nSecondColor = color;
        update();
    }
}

void CoreNode::drawBody(QPainter* pPainter)
{
    int w = static_cast<int>(width());
    int h = static_cast<int>(height());

    pPainter->fillRect(0, 0, w, h, QBrush(nBackgroundColor));

    QLinearGradient g(QPoint(0, 0), QPoint(w, nPanelHeight));
    g.setColorAt(0, nFirstColor);
    g.setColorAt(1, nSecondColor);
    pPainter->fillRect(0, 0, w, nPanelHeight, QBrush(g));


    pPainter->setPen(nHighlightColor);
    pPainter->drawRect(1, 1, w - 2, h - 2);
    pPainter->drawRect(1, 1, w, nPanelHeight - 2);
}

void CoreNode::drawTitle(QPainter* pPainter)
{
    pPainter->setPen(nTitleColor);
    pPainter->setFont(nTitleFont);
    QFontMetrics f(nTitleFont);
    int x = f.width(nTitle);
    int y = f.height();
    pPainter->drawText(x / 2, y, nTitle);
}

void CoreNode::drawPorts(QPainter* pPainter)
{
    pPainter->setRenderHint(QPainter::RenderHint::Antialiasing, true);
    for (int i = 0; i < nInputPorts.length(); i++)
    {
        pPainter->setBrush(nInputPorts[i].nColor);
        int r = static_cast<int>(nInputPorts[i].nRadius);
        pPainter->drawEllipse(nInputPorts[i].nPosition, r, r);
    }
    for (int i = 0; i < nOutputPorts.length(); i++)
    {
        pPainter->setBrush(nOutputPorts[i].nColor);
        int r = static_cast<int>(nOutputPorts[i].nRadius);
        pPainter->drawEllipse(nOutputPorts[i].nPosition, r, r);
    }
}

void CoreNode::drawLabels(QPainter* pPainter)
{
    for (int i = 0; i < nLabels.length(); i++)
    {
        nLabels[i].drawBody(pPainter);
    }
}

void CoreNode::drawNumberBoxes(QPainter* pPainter)
{
    for (int i = 0; i < nNumberBoxes.length(); i++)
    {
        nNumberBoxes[i].drawBody(pPainter, npCurrentNumberBox);
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
    if (nIsMouseClickedOnHeader)
    {
        QPoint curr = QPoint(static_cast<int>(position().x()), static_cast<int>(position().y()));
        QPoint l = curr - nLastMousePosition + pEvent->pos();
        setPosition(l);
    }
    portLineMoveHelper(pEvent->pos());
}

void CoreNode::mousePressEvent(QMouseEvent* pEvent)
{
    setFocus(true);
    nLastMousePosition = pEvent->pos();
    if (isMouseOnHeader(pEvent->pos()))
    {
        nIsMouseClickedOnHeader = true;
    }
    else
    {
        portClickHelper(pEvent->pos());
        numberBoxClickHelper(pEvent->pos());
    }
}

void CoreNode::mouseReleaseEvent(QMouseEvent* pEvent)
{
    nIsMouseClickedOnHeader = false;
    releasePortTargeter(pEvent->pos());
}

void CoreNode::focusOutEvent(QFocusEvent* pEvent)
{
    if (pEvent->lostFocus())
    {
        npCurrentNumberBox = nullptr;
        update();
    }
}

void CoreNode::keyPressEvent(QKeyEvent* pEvent)
{
    if (npCurrentNumberBox != nullptr)
    {
        npCurrentNumberBox->keyPress(pEvent);
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
        pBoard->mCurrentPortType = pPort->nType;
        pBoard->mCurrentLineColor = pPort->nColor;
        pBoard->mFromCurrentLine = pPort->getWorldPosition();
        pBoard->mToCurrentLine = point + convertQPoint(position());
        if (pPort->nType == Port::PortType::INPUT)
        {
            nIsInputPortClicked = true;

        }
        else
        {
            nIsOutPutPortClicked = true;
        }
        nCurrentPort = pPort;
    }
}

void CoreNode::numberBoxClickHelper(const QPoint& point)
{
    NumberBox* pNumberBox = getClickedNumberBox(point);
    if (pNumberBox != nullptr)
    {
        npCurrentNumberBox = pNumberBox;
    }
    else
    {
        npCurrentNumberBox = nullptr;

    }
    update();
}

NumberBox* CoreNode::getClickedNumberBox(const QPoint& point)
{
    NumberBox* pPort{};

    for (int i = 0; i < nNumberBoxes.length(); i++)
    {
        if (abs(point.x() - nNumberBoxes[i].nPosition.x()) <= nNumberBoxes[i].nWidth)
        {
            if (abs(point.y() - nNumberBoxes[i].nPosition.y()) <= nNumberBoxes[i].nHeight)
            {
                pPort = &nNumberBoxes[i];
            }
        }
    }
    return pPort;
}

Port* CoreNode::getClickedPort(const QPoint& point)
{
    Port* pPort{};

    for (int i = 0; i < nOutputPorts.length(); i++)
    {
        if (abs(point.x() - nOutputPorts[i].nPosition.x()) <= nOutputPorts[i].nRadius)
        {
            if (abs(point.y() - nOutputPorts[i].nPosition.y()) <= nOutputPorts[i].nRadius)
            {
                pPort = &nOutputPorts[i];
            }
        }
    }
    for (int i = 0; i < nInputPorts.length(); i++)
    {
        if (abs(point.x() - nInputPorts[i].nPosition.x()) <= nInputPorts[i].nRadius)
        {
            if (abs(point.y() - nInputPorts[i].nPosition.y()) <= nInputPorts[i].nRadius)
            {
                pPort = &nInputPorts[i];
            }
        }
    }
    return pPort;
}

void CoreNode::portLineMoveHelper(const QPoint& point)
{
    if (nIsInputPortClicked || nIsOutPutPortClicked)
    {
        Board* pBoard = dynamic_cast<Board*>(parent());
        pBoard->mToCurrentLine = point + convertQPoint(position());
        pBoard->mFromCurrentLine = nCurrentPort->getWorldPosition();
    }
    dynamic_cast<QQuickItem*>(parent())->update();
}

void CoreNode::releasePortTargeter(const QPoint& point)
{
    Board* pBoard = dynamic_cast<Board*>(parent());
    pBoard->mIsDrawCurrentLine = false;
    pBoard->update();
    if (nIsInputPortClicked)
    {
        nIsInputPortClicked = false;
        Port* pPort{};
        pPort = pPort->getPortNearestAtPosition(point + convertQPoint(position()), parent(), this);
        if (pPort != nullptr)
        {
            if (pPort->nType == Port::PortType::OUTPUT)
            {
                bindPort(pPort, nCurrentPort);
            }
        }
        else
        {
            connectionRemover();
        }
    }
    if (nIsOutPutPortClicked)
    {
        nIsOutPutPortClicked = false;
        Port* pPort{};
        pPort = pPort->getPortNearestAtPosition(point + convertQPoint(position()), parent(), this);
        if (pPort != nullptr)
        {
            if (pPort->nType == Port::PortType::INPUT)
            {
                bindPort(nCurrentPort, pPort);
            }
        }
        else
        {
            connectionRemover();
        }
    }
    nCurrentPort = nullptr;
}

void CoreNode::connectionRemover()
{
    if (nCurrentPort == nullptr)
    {
        return;
    }
    if (nCurrentPort->nType == Port::PortType::INPUT)
    {
        nCurrentPort->nTarget = nullptr;
    }
    else
    {
        if (nCurrentPort->nInput != nullptr)
        {
            nCurrentPort->nInput->nTarget = nullptr;
        }
    }
}

void CoreNode::bindPort(Port* pPort1, Port* pPort2)
{
    pPort2->nTarget = pPort1;
    pPort1->nInput = pPort2;
}