#pragma once

#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include <QProcess>
#include <QTextStream>

class ResultParser : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QString orderResult(QString result);
};
