#pragma once

#include <QQuickPaintedItem>
#include <QPainter>

#define DEFAULT_SQUARE_DIMENSION 25
#define MAX_ZOOM 1.25f
#define MIN_ZOOM 0.75f

class BlackBoard : public QQuickPaintedItem
{
    Q_OBJECT

        Q_PROPERTY(bool rightClicked READ rightClicked NOTIFY onRightMouseClickChanged)

public:
    BlackBoard() { setAcceptedMouseButtons(Qt::AllButtons); };
    bool rightClicked() const { return mIsRighClicked; };


protected:
    void paint(QPainter* painter) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

signals:
    void onRightMouseClickChanged(const bool&);

public slots:

private:
    QColor mBackgroundColor{ 50, 50, 50 };
    QColor mSmallLineColor{ 38, 38, 38 };
    QColor mLargeLineColor{ 28, 28, 28 };

    QPoint mMouseDownPosition;
    bool mIsMouseDown{};

    int mSquareDimension{ 25 };
    int mSquareNumber{ 5 };
    bool mIsRighClicked{};
    float mCurZoom{ 1 };

    void drawGridLines(QPainter* painter);
    void zoomAmountModifier(int amt);
    void zoom(float amt);
    void zoomNodes();
};
