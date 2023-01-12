#include "nodevaluefinder.h"

QString NodeValueFinder::getResult(BlackBoard* blackboard)
{
    QList<CoreNode*> allNodes;
    QList<CoreNode*> inputNodeOnly;

    QObjectList children = blackboard->children();
    for (int i = 0; i < children.size(); i++)
    {
        CoreNode* c = dynamic_cast<CoreNode*>(children[i]);
        if (c != nullptr)
        {
            allNodes.push_back(c);

            if (c->mOutputPorts.length() == 0)
                inputNodeOnly.append(c);
        }
    }

    QString res = "";

    for (int i = 0; i < inputNodeOnly.size(); i++)
    {

        res += inputNodeOnly[i]->resultString() + "\r\n";
    }

    ResultParser p;

    return p.orderResult(res);
}
