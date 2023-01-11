#include "corenode.h"

QString CoreNode::resultString()
{
    QString result = functionName;
    for (int j = 0; j < outputPort.length(); j++)
    {
        for (int k = 0; k < outputPort[j].numberBoxList.length(); k++)
        {
            for (int l = 0; l < numberBoxList.length(); l++)
            {
                result += numberBoxList[l].text + "";
            }
        }
    }

    if (inputPort.length() != 0)
    {
        result += "(";
    }

    for (int i = 0; i < inputPort.length(); i++)
    {
        Port* port = inputPort[i].target;
        if (port == nullptr)
        {
            continue;
        }

        result += dynamic_cast<CoreNode*>(inputPort[i].target->parent)->resultString();
        if (i != inputPort.length() - 1)
        {
            result += ",";
        }
    }

    if (inputPort.length() != 0)
    {
        result += ")";
    }

    return result;
}

void CoreNode::paint(QPainter*)
{

}
