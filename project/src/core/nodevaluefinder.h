#pragma once

#include <QObject>

#include "blackboard.h"
#include "nodes/corenode.h"
#include "resultparser.h"

class NodeValueFinder : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString getResult(BlackBoard*);
};
