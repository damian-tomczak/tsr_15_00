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
    CoreNode(const char* functionName) : nFunctionName(functionName) { setAcceptedMouseButtons(Qt::AllButtons); }
    QList<Port> nInputPorts;
    QList<Port> nOutputPorts;
    QList<NumberBox> nNumberBoxes;
    QList<Label> nLabels;
    QString nFunctionName;

    QString resultString();

    QColor firstColor() const;
    QColor secondColor() const;
    int panelHeight() const { return nPanelHeight; }

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
    QString nTitle{ "Node" };
    QColor nTitleColor{ Qt::white };
    QFont nTitleFont{ "Segoe UI", 12, -1, true };
    QColor nFirstColor{ Qt::blue };
    QColor nSecondColor{ Qt::green };
    QColor nBackgroundColor{ 40, 40, 40 };
    int nPanelHeight{ 40 };
    QColor nHighlightColor{ Qt::yellow };

    Port* nCurrentPort{};
    NumberBox* npCurrentNumberBox{};

    QPoint nLastMousePosition;
    bool nIsMouseClickedOnHeader{};
    bool nIsOutPutPortClicked{};
    bool nIsInputPortClicked{};

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
    void portLineMoveHelper(const QPoint& point);
    void releasePortTargeter(const QPoint& point);
    void connectionRemover();
    void bindPort(Port* pPort1, Port* pPort2);
};