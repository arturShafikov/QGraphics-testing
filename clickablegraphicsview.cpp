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
    draggedItem = itemAt(e->pos());
    QPointF currentPoint = mapToScene(e->pos());
    initialPoint = currentPoint;
    if (draggedItem->type() != QGraphicsEllipseItem::Type) {
        draggedItem = nullptr;
        roi.addPoint(scene->addEllipse(currentPoint.x()-pointRadius,
                                       currentPoint.y()-pointRadius,
                       pointRadius*2.0, pointRadius*2.0,
                       QPen(), QBrush(Qt::SolidPattern)));
        if (!isFirstPoint) {
            QLineF line(lastPoint.x(), lastPoint.y(),
                        currentPoint.x(), currentPoint.y());

            roi.addLine(scene->addLine(line));
        }
        if (isFirstPoint) {
            firstPoint = currentPoint;
            isFirstPoint = false;
        }
        lastPoint = currentPoint;
    }
}

void ClickableGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if (draggedItem) {
        QPointF currentPoint = mapToScene(event->pos());
        roi.changePointPosition(draggedItem,
                                currentPoint.rx() - initialPoint.rx(),
                                currentPoint.ry() - initialPoint.ry());
        initialPoint = currentPoint;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ClickableGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsItem *foundItem = itemAt(event->pos());
    if (foundItem && draggedItem &&
            foundItem != draggedItem) {
        QPointF currentPoint = mapToScene(event->pos());
        roi.changePointPosition(draggedItem,
                                currentPoint.rx() - initialPoint.rx(),
                                currentPoint.ry() - initialPoint.ry());
    }
    draggedItem = nullptr;
    initialPoint = QPointF(0,0);
    QGraphicsView::mouseReleaseEvent(event);
}

void ClickableGraphicsView::setImage(QImage image)
{
    imageItem = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    this->setFixedSize(image.width(), image.height());
    scene->addItem(imageItem);
}

void ClickableGraphicsView::closePoints()
{
    QLineF line(lastPoint.x(), lastPoint.y(),
                firstPoint.x(), firstPoint.y());
    roi.addLine(scene->addLine(line));
}

void ClickableGraphicsView::clearItems()
{
    roi.clearItems();
    isFirstPoint = true;
}

