#pragma once

#include <QQuickPaintedItem>

#include "core/numberboxcore.hpp"
#include "core/port.h"
#include "core/label.hpp"

class CoreNode : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CoreNode(const char* functionName) : mFunctionName(functionName) {}
    QList<Port> mInputPorts;
    QList<Port> mOutputPorts;
    QList<NumberBox> mNumberBoxes;
    QList<Label> mLabels;
    QString mFunctionName;

    QString resultString();

    QColor firstColor() const;
    QColor secondColor() const;

public slots:
    void setTitle(const QString title);
    void setFirstColor(const QColor color);
    void setSecondColor(const QColor color);

protected:
    void paint(QPainter* painter) override;

private:
    QString mTitle{ "Node" };
    QColor mTitleColor{ Qt::white };
    QFont mTitleFont{ "Segoe UI", 12, -1, true };
    QColor mFirstColor{ Qt::blue };
    QColor mSecondColor{ Qt::green };
    QColor mBackgroundColor{ 40, 40, 40 };
    int mPanelHeight{ 40 };
    QColor mHighlightColor{ Qt::yellow };

    Port* mCurrentPort;
    NumberBox* mpCurrentNumberBox;

    void drawBody(QPainter* painter);
    void drawTitle(QPainter* painter);
    void drawPorts(QPainter* painter);
    void drawLabels(QPainter* painter);
    void drawNumberBoxes(QPainter* painter);
};