#pragma once

#include <QObject>

#include "blackboard.h"
#include "nodecore.h"
#include "resultparser.h"

class NodeValueFinder : public QObject
{
    Q_OBJECT

    Q_INVOKABLE QString getResult(BlackBoard*);
};
