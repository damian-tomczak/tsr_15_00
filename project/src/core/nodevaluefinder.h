#pragma once

#include <QObject>

#include "board.h"
#include "nodes/corenode.h"
#include "resultparser.h"

class NodeValueFinder : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QString correctAnswer READ getAnswer WRITE setAnswer)

public:
    Q_INVOKABLE QString getResult(Board* board);

signals:
    void correctAnswer();

public slots:
    void setAnswer(QString answer) { mAnswer = answer; }
    QString getAnswer() { return mAnswer; }

private:
    QString mAnswer;
};
