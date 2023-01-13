#pragma once

#include <QObject>

#include "board.h"
#include "nodes/corenode.h"
#include "resultparser.h"

class NodeValueFinder : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString getResult(Board*);
};
