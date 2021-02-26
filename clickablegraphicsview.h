#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <QtMath>
#include <QScrollBar>
#include <iostream>
#include <regionofinterest.h>

class ClickableGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    ClickableGraphicsView(QWidget *parent = 0);
public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void setImage(QImage image);
    void closePoints();
    void clearItems();
    void cancel();
    void drawBoundingRect();
    void deletePoint();
    void enableCreationMode();
    void hide(bool needToHide);
private:
    QGraphicsScene *scene;
    bool isFirstPoint = true;
    QGraphicsItem *draggedItem;
    QGraphicsEllipseItem *selectedPoint = nullptr;
    const double pointRadius = 7;
    const double activePointRadius = 9;
    QGraphicsPixmapItem* imageItem;
    QPointF initialDragPoint;
    RegionOfInterest roi;
    bool isClosed = false;
    QGraphicsItem *boundingBox = nullptr;
    enum Modes {
        MODE_EMPTY = -1,
        MODE_CREATION = 1,
        MODE_READY = 2
    };
    int currentMode = MODE_EMPTY;
    void addPoint(QPointF point);
};

#endif // CLICKABLEGRAPHICSVIEW_H
