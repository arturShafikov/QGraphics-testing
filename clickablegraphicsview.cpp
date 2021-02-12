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
    double radius = 2;
    QPointF currentPoint = mapToScene(e->pos());
    itemList << scene->addEllipse(currentPoint.x()-radius, currentPoint.y()-radius,
                      radius*2.0, radius*2.0,
                      QPen(), QBrush(Qt::SolidPattern));
    if (!isFirstPoint) {
        QLineF line(lastPoint.x(), lastPoint.y(),
                    currentPoint.x(), currentPoint.y());
        itemList << scene->addLine(line);
    }
    if (isFirstPoint) {
        firstPoint = currentPoint;
        isFirstPoint = false;
    }
    lastPoint = currentPoint;
}

void ClickableGraphicsView::setImage(QImage image)
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    this->setFixedSize(image.width(), image.height());
    scene->addItem(item);
}

void ClickableGraphicsView::closePoints()
{
    QLineF line(lastPoint.x(), lastPoint.y(),
                firstPoint.x(), firstPoint.y());
    itemList << scene->addLine(line);
}

void ClickableGraphicsView::clearItems()
{
    for (int i = 0; i < itemList.size(); i++) {
        delete itemList.at(i);
    }
    itemList.clear();
    isFirstPoint = true;
}

