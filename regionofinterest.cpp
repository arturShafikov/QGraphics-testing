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

QPointF RegionOfInterest::getPreLastPointCoordinates()
{
    if (pointCoordinatesList.size() < 2) {
        return QPointF(0,0);
    } else {
        return pointCoordinatesList.at(pointCoordinatesList.size()-2);
    }
}

QPointF RegionOfInterest::getFirstPointCoordinates()
{
    if (pointCoordinatesList.isEmpty()) {
        return QPointF(0,0);
    } else {
        return pointCoordinatesList.front();
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

QRectF RegionOfInterest::getBoundingRect(QGraphicsItemGroup *group)
{
    for (int i = 0; i < pointList.size(); i++) {
        group->addToGroup(pointList.at(i));
    }
    for (int i = 0; i < lineList.size(); i++) {
        group->addToGroup(lineList.at(i));
    }
    return group->boundingRect();
}

int RegionOfInterest::getPointCount()
{
    return pointList.size();
}

void RegionOfInterest::deletePoint(QGraphicsItem *item)
{
    int pointPosition = pointList.indexOf(item);
    if (!lineList.isEmpty()) {
        if ((pointPosition == 0)
                && (lineList.size() == pointList.size())) {
            if (pointList.size() == 3) {
                delete lineList.back();
                lineList.last() = nullptr;
            } else {
                lineList.back()->setLine(
                        lineList.back()->line().x1(),
                        lineList.back()->line().y1(),
                        pointCoordinatesList.at(pointPosition+1).x(),
                        pointCoordinatesList.at(pointPosition+1).y());
            }
        } else if ((pointPosition == (pointList.size()-1))
                   && (lineList.at(pointPosition-1) != nullptr)) {
            if (pointList.size() == 3) {
                delete lineList.at(pointPosition-1);
                lineList[pointPosition-1] = nullptr;
            } else {
                lineList.at(pointPosition-1)->setLine(
                        lineList.at(pointPosition-1)->line().x1(),
                        lineList.at(pointPosition-1)->line().y1(),
                        pointCoordinatesList.front().x(),
                        pointCoordinatesList.front().y());
            }
        } else if ((pointPosition != 0)
                   && (lineList.at(pointPosition-1) != nullptr)) {
            if (pointList.size() == 3) {
                delete lineList.at(pointPosition-1);
                lineList[pointPosition-1] = nullptr;
            } else {
                lineList.at(pointPosition-1)->setLine(
                            lineList.at(pointPosition-1)->line().x1(),
                            lineList.at(pointPosition-1)->line().y1(),
                            pointCoordinatesList.at(pointPosition+1).x(),
                            pointCoordinatesList.at(pointPosition+1).y());
            }
        }
        if (lineList.size() > 1) {
            delete lineList.at(pointPosition);
            lineList[pointPosition] = nullptr;
        } else {
            delete lineList.at(0);
            lineList[0] = nullptr;
        }
        lineList.erase(std::remove(std::begin(lineList), std::end(lineList), nullptr),
                     std::end(lineList));
    }
    delete item;
    pointList.removeAt(pointPosition);
    pointCoordinatesList.removeAt(pointPosition);
}

void RegionOfInterest::hide(bool needToHide)
{
    for (int i = 0; i < pointList.size(); i++) {
        if (needToHide) {
            pointList.at(i)->hide();
        } else {
            pointList.at(i)->show();
        }
    }
    for (int i = 0; i < lineList.size(); i++) {
        if (needToHide) {
            lineList.at(i)->hide();
        } else {
            lineList.at(i)->show();
        }
    }
}
