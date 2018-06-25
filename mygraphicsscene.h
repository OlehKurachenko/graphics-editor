#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QLineF>

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
    QGraphicsItem* tempItem;
    QList<QGraphicsItem *> selectedItems;

public slots:
    void addLine();
    void addCircle();
    void addRect();
    void removeSelected();
    void selection();


};

template <typename T>
T min(const T& a, const T& b){
    if(a<b)
        return a;
    return b;
}

template <typename T>
T max(const T& a, const T& b){
    if(a<b)
        return b;
    return a;
}


#endif // MYGRAPHICSSCENE_H
