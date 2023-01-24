#pragma once

#include <QQuickPaintedItem>

#include "core/numberbox.hpp"
#include "core/port.h"
#include "core/label.hpp"
#include "core/board.h"

class CoreNode : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(bool destructible READ getDestructible WRITE setDestructible)
        Q_PROPERTY(bool editable READ getEditable WRITE setEditable)

public:
    CoreNode(const char* functionName) : mFunctionName(functionName) { setAcceptedMouseButtons(Qt::AllButtons); }

    QList<Port> mInputPorts;
    QList<Port> mOutputPorts;
    QList<Label> mLabels;
    NumberBox* mpNumberBox{};
    QString mFunctionName;

    QString resultString();

    QColor firstColor() const { return mFirstColor; }
    QColor secondColor() const { return mSecondColor; }
    int panelHeight() const { return mPanelHeight; }

public slots:
    void setTitle(const QString title) { mTitle = title; update(); };
    void setFirstColor(const QColor color) { mFirstColor = color; update(); };
    void setSecondColor(const QColor color) { mSecondColor = color; update(); };
    void setDestructible(const bool condition) { mIsDestructible = condition; }
    bool getDestructible() const { return mIsDestructible; }
    void setEditable(const bool condition) { mIsEditable = condition; }
    bool getEditable() const { return mIsEditable; }

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
    QPoint mLastMousePosition;
    bool mIsMouseClickedOnHeader{};
    bool mIsOutPutPortClicked{};
    bool mIsInputPortClicked{};
    bool mIsDestructible{ true };
    bool mIsEditable{ true };

    void drawBody(QPainter* pPainter);
    void drawTitle(QPainter* pPainter);
    void drawPorts(QPainter* pPainter);
    void drawLabels(QPainter* pPainter);
    void drawNumberBox(QPainter* pPainter);

    bool isMouseOnHeader(const QPoint& point);
    void portClickHelper(const QPoint& point);
    void numberBoxClickHelper(const QPoint& point);

    bool isClickedNumberBox(const QPoint& point);
    Port* getClickedPort(const QPoint& point);
    void portLineMoveHelper(const QPoint& point);
    void releasePortTargeter(const QPoint& point);
    void connectionRemover();
    void bindPort(Port* pPort1, Port* pPort2) { pPort2->mTarget = pPort1; pPort1->mInput = pPort2; }
};