#include "corenode.h"

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

void CoreNode::paint(QPainter*)
{

}