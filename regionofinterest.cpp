#include "regionofinterest.h"

RegionOfInterest::RegionOfInterest()
{

}

void RegionOfInterest::addPoint(QGraphicsItem *item, int x, int y)
{
    pointList.push_back(item);
    pointCoordinatesList.push_back(QPointF(x,y));
}

void RegionOfInterest::addLine(QGraphicsLineItem *item)
{
    lineList.push_back(item);
}

void RegionOfInterest::changePointPosition(QGraphicsItem *item, qreal x, qreal y)
{
    item->moveBy(x,y);
    int pointPosition = pointList.indexOf(item);
    pointCoordinatesList[pointPosition].rx() += x;
    pointCoordinatesList[pointPosition].ry() += y;
    if (!lineList.isEmpty()) {
        if ((pointPosition == 0) && (lineList.size() == pointList.size())) {
            lineList.back()->setLine(
                        lineList.back()->line().x1(),
                        lineList.back()->line().y1(),
                        lineList.back()->line().x2() + x,
                        lineList.back()->line().y2() + y);
        } else if ((pointPosition != 0) && (lineList.at(pointPosition-1) != nullptr)) {
            lineList.at(pointPosition-1)->setLine(
                        lineList.at(pointPosition-1)->line().x1(),
                        lineList.at(pointPosition-1)->line().y1(),
                        lineList.at(pointPosition-1)->line().x2() + x,
                        lineList.at(pointPosition-1)->line().y2() + y);
        }
        if (lineList.size() > pointPosition) {
            lineList.at(pointPosition)->setLine(
                        lineList.at(pointPosition)->line().x1() + x,
                        lineList.at(pointPosition)->line().y1() + y,
                        lineList.at(pointPosition)->line().x2(),
                        lineList.at(pointPosition)->line().y2());
        }
    }
}

void RegionOfInterest::clearItems()
{
    for (int i = 0; i < pointList.size(); i++) {
        delete pointList.at(i);
    }
    pointList.clear();
    pointCoordinatesList.clear();

    for (int i = 0; i < lineList.size(); i++) {
        delete lineList.at(i);
    }
    lineList.clear();
}

QGraphicsItem *RegionOfInterest::getFirstPoint()
{
    if (pointList.isEmpty()) {
        return nullptr;
    } else {
        return pointList.first();
    }
}

QGraphicsItem *RegionOfInterest::getLastPoint()
{
    if (pointList.isEmpty()) {
        return nullptr;
    } else {
        return pointList.back();
    }
}

QPointF RegionOfInterest::getLastPointCoordinates()
{
    if (pointCoordinatesList.isEmpty()) {
        return QPointF(0,0);
    } else {
        return pointCoordinatesList.back();
    }
}

void RegionOfInterest::removeLastAddedElement()
{
    if (!pointList.isEmpty()) {
        delete pointList.back();
        pointList.removeLast();
        pointCoordinatesList.removeLast();
    }
    removeLastLine();
}

void RegionOfInterest::removeLastLine()
{
    if (!lineList.isEmpty()) {
        delete lineList.back();
        lineList.removeLast();
    }
}
