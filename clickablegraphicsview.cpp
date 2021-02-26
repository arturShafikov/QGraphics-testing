#include "clickablegraphicsview.h"

ClickableGraphicsView::ClickableGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    this->setScene(scene);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ClickableGraphicsView::mousePressEvent(QMouseEvent *e)
{
    switch (currentMode) {
        case MODE_CREATION: {
           if ((!isClosed)&&
                   (itemAt(e->pos()) == roi.getFirstPoint())&&
                   (roi.getPointCount() > 1)) {
               closePoints();
               currentMode = MODE_READY;
               return;
           }
           addPoint(mapToScene(e->pos()));
           break;
        }
    default:
        break;
    }
//    draggedItem = itemAt(e->pos());
//    QPointF currentPoint = mapToScene(e->pos());
//    initialDragPoint = currentPoint;
//    if ((!isClosed)&&
//            (draggedItem == roi.getFirstPoint())&&
//            (roi.getPointCount() > 1)) {
//        closePoints();
//        return;
//    }
//    if (draggedItem->type() != QGraphicsEllipseItem::Type) {
//        draggedItem = nullptr;
//        roi.addPoint(scene->addEllipse(currentPoint.x()-pointRadius,
//                                       currentPoint.y()-pointRadius,
//                       pointRadius*2.0, pointRadius*2.0,
//                       QPen(), QBrush(Qt::SolidPattern)),
//                     currentPoint.x(), currentPoint.y());
//        if (!isFirstPoint) {
//            QLineF line(roi.getPreLastPointCoordinates().x(),
//                        roi.getPreLastPointCoordinates().y(),
//                        currentPoint.x(), currentPoint.y());

//            roi.addLine(scene->addLine(line));
//        }
//        if (isFirstPoint) {
//            isFirstPoint = false;
//        }
//    } else {
//        if (selectedPoint != nullptr) {
//            selectedPoint->setRect(
//                        selectedPoint->rect().x(),
//                        selectedPoint->rect().y(),
//                        pointRadius*2,
//                        pointRadius*2);
//        }
//        selectedPoint = dynamic_cast<QGraphicsEllipseItem*>(draggedItem);
//        selectedPoint->setRect(
//                    selectedPoint->rect().x(),
//                    selectedPoint->rect().y(),
//                    activePointRadius*2,
//                    activePointRadius*2);
//    }
}

void ClickableGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
//    if (draggedItem) {
//        QPointF currentPoint = mapToScene(event->pos());
//        qreal difX = currentPoint.rx() - initialDragPoint.rx();
//        qreal difY = currentPoint.ry() - initialDragPoint.ry();
//        roi.changePointPosition(draggedItem,
//                                difX,
//                                difY);
//        initialDragPoint = currentPoint;
//    }
//    QGraphicsView::mouseMoveEvent(event);
}

void ClickableGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
//    QGraphicsItem *foundItem = itemAt(event->pos());
//    if (foundItem && draggedItem &&
//            foundItem != draggedItem) {
//        QPointF currentPoint = mapToScene(event->pos());
//        qreal difX = currentPoint.rx() - initialDragPoint.rx();
//        qreal difY = currentPoint.ry() - initialDragPoint.ry();
//        roi.changePointPosition(draggedItem,
//                                difX,
//                                difY);
//    }
//    initialDragPoint = QPointF(0,0);
//    QGraphicsView::mouseReleaseEvent(event);
}

void ClickableGraphicsView::wheelEvent(QWheelEvent *event)
{
    const QPointF scenePoint = mapToScene(QPoint(event->position().x(),
                                                 event->position().y()));
    qreal factor = qPow(1.2, event->angleDelta().y()/240.0);
    scale(factor, factor);
    const QPointF mousePoint = mapFromScene(scenePoint);
    const QPointF movePoint = mousePoint - QPoint(event->position().x(),
                                                  event->position().y());
    horizontalScrollBar()->setValue(movePoint.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(movePoint.y() + verticalScrollBar()->value());

}

void ClickableGraphicsView::setImage(QImage image)
{
    imageItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    this->setFixedSize(image.width(), image.height());
    scene->addItem(imageItem);
}

void ClickableGraphicsView::closePoints()
{
    QLineF line(roi.getLastPointCoordinates().x(), roi.getLastPointCoordinates().y(),
                roi.getFirstPointCoordinates().x(), roi.getFirstPointCoordinates().y());
    roi.addLine(scene->addLine(line));
    isClosed = true;
}

void ClickableGraphicsView::clearItems()
{
    roi.clearItems();
    isFirstPoint = true;
    isClosed = false;
}

void ClickableGraphicsView::cancel()
{
    if (isClosed) {
        roi.removeLastLine();
        isClosed = false;
    } else {
        roi.removeLastAddedElement();
    }
    if (roi.getFirstPoint() == nullptr) {
        isFirstPoint = true;
    }
}

void ClickableGraphicsView::drawBoundingRect()
{
    if (boundingBox == nullptr) {
        QList<QGraphicsItem*> list;
        QGraphicsItemGroup *group = scene->createItemGroup(list);
        boundingBox = scene->addRect(roi.getBoundingRect(group));
    } else {
        delete boundingBox;
        boundingBox = nullptr;
    }
}

void ClickableGraphicsView::deletePoint()
{
    roi.deletePoint(draggedItem);
    draggedItem = nullptr;
    selectedPoint = nullptr;
}

void ClickableGraphicsView::enableCreationMode()
{
    if (currentMode == MODE_EMPTY) {
        currentMode = MODE_CREATION;
    }
}

void ClickableGraphicsView::hide(bool needToHide)
{
    if (currentMode == MODE_READY) {
        roi.hide(needToHide);
    }
}

void ClickableGraphicsView::addPoint(QPointF point)
{
    roi.addPoint(scene->addEllipse(point.x()-pointRadius,
                                   point.y()-pointRadius,
                   pointRadius*2.0, pointRadius*2.0,
                   QPen(), QBrush(Qt::SolidPattern)),
                 point.x(), point.y());
    if (!isFirstPoint) {
        QLineF line(roi.getPreLastPointCoordinates().x(),
                    roi.getPreLastPointCoordinates().y(),
                    point.x(), point.y());

        roi.addLine(scene->addLine(line));
    }
    if (isFirstPoint) {
        isFirstPoint = false;
    }
}

