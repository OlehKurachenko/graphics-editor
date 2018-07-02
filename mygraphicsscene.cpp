#include "mygraphicsscene.h"

#include <algorithm>
using std::min;
using std::max;

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(tempItem or tempItem!=nullptr){
        delete tempItem;
    }
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
    switch(currentDrawingState){
    case DrawingState::Default:
        event->ignore();
        break;
    case DrawingState::LineZero:
        delete tempItem;
        tempItem = new QGraphicsLineItem(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().rx(), event->scenePos().ry());
        this->addItem(tempItem);
        break;
    case DrawingState::RectZero:{
        delete tempItem;
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        tempItem = new QGraphicsRectItem(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        this->addItem(tempItem);
        break;
    }
    case DrawingState::CircleZero:{
        delete tempItem;
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        tempItem = new QGraphicsEllipseItem(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        this->addItem(tempItem);
        break;
    }
    default:
        break;
    }

}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(currentDrawingState==DrawingState::LineZero || currentDrawingState==DrawingState::RectZero || currentDrawingState==DrawingState::CircleZero){
        tempItem = nullptr;
    } else if(currentDrawingState==DrawingState::Default){
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        selectedItems = items(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
    }
}

void MyGraphicsScene::selection() Q_SLOT{
    this->currentDrawingState = DrawingState::Default;
}

void MyGraphicsScene::addLine() Q_SLOT{
    this->currentDrawingState = DrawingState::LineZero;
}

void MyGraphicsScene::addCircle() Q_SLOT{
    this->currentDrawingState = DrawingState::CircleZero;
}

void MyGraphicsScene::addRect() Q_SLOT{
    this->currentDrawingState = DrawingState::RectZero;
}

void MyGraphicsScene::removeSelected(){
    for(auto i:selectedItems){
        delete i;
    }
    selectedItems = QList<QGraphicsItem*>();
}
