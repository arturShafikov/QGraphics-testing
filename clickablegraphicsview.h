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
private:
    QGraphicsScene *scene;
    bool isFirstPoint = true;
    QPointF lastPoint;
    QPointF firstPoint;
    QGraphicsItem *draggedItem;
    QGraphicsEllipseItem *selectedPoint = nullptr;
    const double pointRadius = 7;
    const double activePointRadius = 9;
    QGraphicsPixmapItem* imageItem;
    QPointF initialDragPoint;
    RegionOfInterest roi;
    bool isClosed = false;
    QGraphicsItem *boundingBox = nullptr;
};

#endif // CLICKABLEGRAPHICSVIEW_H
