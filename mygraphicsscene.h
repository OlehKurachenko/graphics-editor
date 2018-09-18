#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QLineF>

#include <iostream>

class MyGraphicsScene: public QGraphicsScene{
    Q_OBJECT
public:
    MyGraphicsScene(qreal x, qreal y, qreal width, qreal height): QGraphicsScene(x,y,width, height), tempItem(nullptr){}

    enum class DrawingState {Default, LineZero, RectZero, CircleZero};
    DrawingState currentDrawingState;

    void mousePressEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent  *mouseEvent) Q_DECL_OVERRIDE;

private:

    void drawBackground(QPainter *painter, const QRectF &rect) override {
        Q_UNUSED(rect);

        std::cout << "Drawing background!" << std::endl;

        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(Qt::black, Qt::SolidPattern));
        painter->setOpacity(0.7);
        painter->drawRect(0, 0, 100, 100);
    }

    QGraphicsItem* tempItem;
    QList<QGraphicsItem *> selectedItems;

public slots:
    void addLine();
    void addCircle();
    void addRect();
    void removeSelected();
    void selection();


};


#endif // MYGRAPHICSSCENE_H
