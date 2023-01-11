#pragma once

#include <QObject>
#include <QCursor>

class Cursor : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE QPoint getCursor(int x, int y) { return QCursor::pos() - QPoint(x, y); }
};
