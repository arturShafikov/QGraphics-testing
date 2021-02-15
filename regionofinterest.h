#ifndef REGIONOFINTEREST_H
#define REGIONOFINTEREST_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <iostream>

class RegionOfInterest
{
public:
    RegionOfInterest();
public slots:
    void addPoint(QGraphicsItem* item);
    void addLine(QGraphicsLineItem *item);
    void changePointPosition(QGraphicsItem* item, qreal x, qreal y);
    void clearItems();
private:
    QList<QGraphicsItem*> pointList;
    QList<QGraphicsLineItem*> lineList;

};

#endif // REGIONOFINTEREST_H
