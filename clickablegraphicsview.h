#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include <iostream>

class ClickableGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    ClickableGraphicsView(QWidget *parent = 0);
public slots:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void setImage(QImage image);
    void closePoints();
    void clearItems();
private:
    QGraphicsScene *scene;
    bool isFirstPoint = true;
    QPointF lastPoint;
    QPointF firstPoint;
    QList<QGraphicsItem *> itemList;
    QGraphicsItem *draggedItem;
    double pointRadius = 5;
    QGraphicsPixmapItem* imageItem;
    QPointF initialPoint;
};

#endif // CLICKABLEGRAPHICSVIEW_H
