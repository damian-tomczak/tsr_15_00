#pragma once

#include <QQuickPaintedItem>

#include "core/numberboxcore.hpp"
#include "core/port.h"
#include "core/label.hpp"
#include "core/board.h"

class CoreNode : public QQuickPaintedItem
{
    Q_OBJECT

public:
    CoreNode(const char* functionName) : mFunctionName(functionName) { setAcceptedMouseButtons(Qt::AllButtons); }
    QList<Port> mInputPorts;
    QList<Port> mOutputPorts;
    QList<NumberBox> mNumberBoxes;
    QList<Label> mLabels;
    QString mFunctionName;

    QString resultString();

    QColor firstColor() const;
    QColor secondColor() const;
    int panelHeight() const { return mPanelHeight; }

public slots:
    void setTitle(const QString title);
    void setFirstColor(const QColor color);
    void setSecondColor(const QColor color);

protected:
    void paint(QPainter* pPainter) override;
    void mouseMoveEvent(QMouseEvent* pEvent) override;
    void mousePressEvent(QMouseEvent* pEvent) override;
    void mouseReleaseEvent(QMouseEvent* pEvent) override;
    void focusOutEvent(QFocusEvent* pEvent) override;
    void keyPressEvent(QKeyEvent* pEvent) override;

private:
    QString mTitle{ "Node" };
    QColor mTitleColor{ Qt::white };
    QFont mTitleFont{ "Segoe UI", 12, -1, true };
    QColor mFirstColor{ Qt::blue };
    QColor mSecondColor{ Qt::green };
    QColor mBackgroundColor{ 40, 40, 40 };
    int mPanelHeight{ 40 };
    QColor mHighlightColor{ Qt::yellow };

    Port* mCurrentPort{};
    NumberBox* mpCurrentNumberBox{};

    QPoint mLastMousePosition;
    bool mIsMouseClickedOnHeader{};
    bool mIsOutPutPortClicked{};
    bool mIsInputPortClicked{};

    void drawBody(QPainter* pPainter);
    void drawTitle(QPainter* pPainter);
    void drawPorts(QPainter* pPainter);
    void drawLabels(QPainter* pPainter);
    void drawNumberBoxes(QPainter* pPainter);

    bool isMouseOnHeader(const QPoint& point);
    void portClickHelper(const QPoint& point);
    void numberBoxClickHelper(const QPoint& point);

    NumberBox* getClickedNumberBox(const QPoint& point);
    Port* getClickedPort(const QPoint& point);
};