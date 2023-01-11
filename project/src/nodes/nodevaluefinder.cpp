#include "nodevaluefinder.h"

QString NodeValueFinder::getResult(BlackBoard* blackboard)
{
    QList<NodeCore*> allNodes;
    QList<NodeCore*> inputNodeOnly;

    QObjectList children = blackboard->children();
    for (int i = 0; i < children.size(); i++)
    {
        NodeCore* c = dynamic_cast<NodeCore*>(children[i]);
        if (c != nullptr)
        {
            allNodes.push_back(c);

            if (c->outputPort.length() == 0)
                inputNodeOnly.append(c);
        }
    }

    QString res = "";

    for (int i = 0; i < inputNodeOnly.size(); i++)
    {

        res += inputNodeOnly[i]->resultString() + "\r\n";
    }

    ResultParser p;

    return p.OoderResult(res);
}
