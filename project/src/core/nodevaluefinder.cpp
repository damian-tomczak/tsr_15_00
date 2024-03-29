#include "nodevaluefinder.h"

QString NodeValueFinder::getResult(Board* pBoard)
{
    QList<CoreNode*> allNodes;
    QList<CoreNode*> inputNodesOnly;

    QObjectList children = pBoard->children();
    for (int i{}; i < children.size(); i++)
    {
        CoreNode* child = dynamic_cast<CoreNode*>(children[i]);
        if (child != nullptr)
        {
            allNodes.push_back(child);

            if (child->mOutputPorts.length() == 0)
            {
                inputNodesOnly.append(child);
            }
        }
    }

    QString result;
    for (int i{}; i < inputNodesOnly.size(); i++)
    {
        result += inputNodesOnly[i]->resultString() + "\r\n";
    }

    ResultParser parser;
    auto outputRaw = parser.orderResult(result);
    auto output = outputRaw.toStdString();
    auto pos = output.find("\r\n");
    if (pos != std::string::npos)
    {
        std::string_view firstResult{ output.begin(), output.begin() + pos };
        if ((mAnswer != "NULL") && (firstResult == mAnswer.toStdString().c_str()))
        {
            emit correctAnswer();
        }

    }
    return outputRaw;
}
