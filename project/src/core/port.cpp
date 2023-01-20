#include "port.h"
#include "nodes/corenode.h"

QPoint Port::getWorldPosition()
{
	return mPosition + QPoint(static_cast<int>(mParent->position().x()), static_cast<int>(mParent->position().y()));
}

Port* Port::getPortNearestAtPosition(QPoint point, QObject* pParent, QQuickItem* pCurrentNode)
{
    Port* pPort{};
    QObjectList children = pParent->children();
    for (int i = 0; i < children.length(); i++)
    {
        CoreNode* pNode = dynamic_cast<CoreNode*>(children[i]);
        if (pNode != dynamic_cast<CoreNode*>(pCurrentNode) && pNode != nullptr)
        {
            for (int j = 0; j < pNode->mInputPorts.length(); j++)
            {
                if (abs(point.x() - pNode->mInputPorts[j].getWorldPosition().x()) <= pNode->mInputPorts[j].mRadius)
                {
                    if (abs(point.y() - pNode->mInputPorts[j].getWorldPosition().y()) <= pNode->mInputPorts[j].mRadius)
                    {
                        pPort = &pNode->mInputPorts[j];
                    }
                }
            }
            for (int j = 0; j < pNode->mOutputPorts.length(); j++)
            {
                if (abs(point.x() - pNode->mOutputPorts[j].getWorldPosition().x()) <= pNode->mOutputPorts[j].mRadius)
                {
                    if (abs(point.y() - pNode->mOutputPorts[j].getWorldPosition().y()) <= pNode->mOutputPorts[j].mRadius)
                    {
                        pPort = &pNode->mOutputPorts[j];
                    }
                }
            }
        }
    }
    return pPort;
}