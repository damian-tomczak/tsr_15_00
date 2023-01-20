#include "port.h"
#include "nodes/corenode.h"

QPoint Port::getWorldPosition()
{
	return nPosition + QPoint(static_cast<int>(nParent->position().x()), static_cast<int>(nParent->position().y()));
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
            for (int j = 0; j < pNode->nInputPorts.length(); j++)
            {
                if (abs(point.x() - pNode->nInputPorts[j].getWorldPosition().x()) <= pNode->nInputPorts[j].nRadius)
                {
                    if (abs(point.y() - pNode->nInputPorts[j].getWorldPosition().y()) <= pNode->nInputPorts[j].nRadius)
                    {
                        pPort = &pNode->nInputPorts[j];
                    }
                }
            }
            for (int j = 0; j < pNode->nOutputPorts.length(); j++)
            {
                if (abs(point.x() - pNode->nOutputPorts[j].getWorldPosition().x()) <= pNode->nOutputPorts[j].nRadius)
                {
                    if (abs(point.y() - pNode->nOutputPorts[j].getWorldPosition().y()) <= pNode->nOutputPorts[j].nRadius)
                    {
                        pPort = &pNode->nOutputPorts[j];
                    }
                }
            }
        }
    }
    return pPort;
}