#ifndef CLICKABLEGRAPHICSVIEW_H
#define CLICKABLEGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>

class ClickableGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    ClickableGraphicsView(QWidget *parent = 0);
public slots:
    void mousePressEvent(QMouseEvent *e);
    void setImage(QImage image);
    void closePoints();
    void clearItems();
private:
    QGraphicsScene *scene;
    bool isFirstPoint = true;
    QPointF lastPoint;
    QPointF firstPoint;
    QList<QGraphicsItem *> itemList;
};

#endif // CLICKABLEGRAPHICSVIEW_H
