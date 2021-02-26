#ifndef REGIONOFINTEREST_H
#define REGIONOFINTEREST_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPointF>
#include <iostream>

class RegionOfInterest
{
public:
    RegionOfInterest();
public slots:
    void addPoint(QGraphicsItem* item, int x, int y);
    void addLine(QGraphicsLineItem *item);
    void changePointPosition(QGraphicsItem* item, qreal x, qreal y);
    void clearItems();
    QGraphicsItem* getFirstPoint();
    QGraphicsItem* getLastPoint();
    QPointF getLastPointCoordinates();
    QPointF getPreLastPointCoordinates();
    QPointF getFirstPointCoordinates();
    void removeLastAddedElement();
    void removeLastLine();
    QRectF getBoundingRect(QGraphicsItemGroup *group);
    int getPointCount();
    void deletePoint(QGraphicsItem* item);
    void hide(bool needToHide);
    void hidePoints(bool needToHide);
private:
    QList<QGraphicsItem*> pointList;
    QList<QPointF> pointCoordinatesList;
    QList<QGraphicsLineItem*> lineList;

};

#endif // REGIONOFINTEREST_H
