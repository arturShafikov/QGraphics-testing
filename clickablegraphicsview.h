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
private:
    QGraphicsScene *scene;
    bool isFirstPoint = true;
    QPointF lastPoint;
    QPointF firstPoint;
    QGraphicsItem *draggedItem;
    double pointRadius = 7;
    QGraphicsPixmapItem* imageItem;
    QPointF initialPoint;
    RegionOfInterest roi;
};

#endif // CLICKABLEGRAPHICSVIEW_H
