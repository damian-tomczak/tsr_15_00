#pragma once

#include <QQuickPaintedItem>
#include <QPainter>

#include "port.h"

#define DEFAULT_SQUARE_DIMENSION 25
#define MAX_ZOOM 1.25f
#define MIN_ZOOM 0.75f

class Board : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(bool rightClicked READ getRightClicked NOTIFY onRightMouseClickChanged)
        Q_PROPERTY(bool darkTheme READ getDarkTheme WRITE setDarkTheme)

public:
    Board() { setAcceptedMouseButtons(Qt::AllButtons); };

    bool mIsDrawCurrentLine{};
    Port::PortType mCurrentPortType{};
    QColor mCurrentLineColor;
    QPoint mFromCurrentLine;
    QPoint mToCurrentLine;

    bool getRightClicked() const { return mIsRighClicked; };
    bool getDarkTheme() const { return mIsDarkTheme; }
    void setDarkTheme(bool condition) { mIsDarkTheme = condition;  }

protected:
    void paint(QPainter* painter) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

signals:
    void onRightMouseClickChanged(const bool&);

private:
    QColor mBackgroundColorDark{ 50, 50, 50 };
    QColor mBackgroundColorLight{ 255, 255, 255 };
    QColor mSmallLineColor{ 38, 38, 38 };
    QColor mLargeLineColor{ 28, 28, 28 };

    QPoint mMouseDownPosition;
    bool mIsMouseDown{};

    int mSquareDimension{ 25 };
    int mSquareNumber{ 5 };
    bool mIsRighClicked{};
    float mCurZoom{ 1 };
    bool mIsDarkTheme{ true };

    void drawGridLines(QPainter* painter);
    void zoomAmountModifier(int amt);
    void zoom(float amt);
    void zoomNodes();

    void drawCurrentLines(QPainter* pPainter);
    void drawConnectors(QPainter* painter);
};
