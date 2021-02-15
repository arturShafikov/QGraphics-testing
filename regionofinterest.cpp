#include "regionofinterest.h"

RegionOfInterest::RegionOfInterest()
{

}

void RegionOfInterest::addPoint(QGraphicsItem *item)
{
    pointList.push_back(item);
}

void RegionOfInterest::addLine(QGraphicsLineItem *item)
{
    lineList.push_back(item);
}

void RegionOfInterest::changePointPosition(QGraphicsItem *item, qreal x, qreal y)
{
    item->moveBy(x,y);
    int pointPosition = pointList.indexOf(item);
    if (pointPosition == 0) {
        lineList.back()->setLine(
                    lineList.back()->line().x1(),
                    lineList.back()->line().y1(),
                    lineList.back()->line().x2() + x,
                    lineList.back()->line().y2() + y);
    } else {
        lineList.at(pointPosition-1)->setLine(
                    lineList.at(pointPosition-1)->line().x1(),
                    lineList.at(pointPosition-1)->line().y1(),
                    lineList.at(pointPosition-1)->line().x2() + x,
                    lineList.at(pointPosition-1)->line().y2() + y);
    }
    lineList.at(pointPosition)->setLine(
                lineList.at(pointPosition)->line().x1() + x,
                lineList.at(pointPosition)->line().y1() + y,
                lineList.at(pointPosition)->line().x2(),
                lineList.at(pointPosition)->line().y2());
}

void RegionOfInterest::clearItems()
{
    for (int i = 0; i < pointList.size(); i++) {
        delete pointList.at(i);
    }
    pointList.clear();

    for (int i = 0; i < lineList.size(); i++) {
        delete lineList.at(i);
    }
    lineList.clear();
}
