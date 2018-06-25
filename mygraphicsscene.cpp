#include "mygraphicsscene.h"

//unsigned pressedCounter = 0;
void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    //++pressedCounter;
    //qDebug()<<"press event "<<pressedCounter;

    if(tempItem or tempItem!=nullptr){
        //this->removeItem(tempItem);
        delete tempItem;
    }
    /*
    switch(currentDrawingState){
    case DrawingState::Default:
        event->ignore();
        break;
    case DrawingState::LineZero:

    }
    */

    /*
    switch(currentDrawingState){
    case DrawingState::Default:
        event->ignore();
        break;
    case DrawingState::LineZero:
        if(tempItem or tempItem!=nullptr){
            //this->removeItem(tempItem);
            delete tempItem;
        }
        //const QLineF line(event->pos(), event->pos());
        //tempItem = this->addLine(line);//

        //tempItem = new QGraphicsLineItem(event->pos().rx(), event->pos().ry(), event->pos().rx(), event->pos().ry());
        //this->addItem(tempItem);
        break;
    default:
        break;
    }
    */
}

//unsigned moveCounter = 0;
void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
    //++moveCounter;
    //qDebug()<<"move event "<<moveCounter;

    //qDebug()<<static_cast<int>(currentDrawingState);

    switch(currentDrawingState){
    case DrawingState::Default:
        //qDebug()<<"Default";
        event->ignore();
        break;
    case DrawingState::LineZero:
        //qDebug()<<"LineZero";
        //this->removeItem(tempItem);
        delete tempItem;
        //const QLineF line(event->buttonDownScenePos(Qt::MouseButton::LeftButton), event->pos());
        //qDebug()<<event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx()<<' '<< event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry()<<" -- "<<event->scenePos().rx()<<' '<<event->scenePos().ry();
        tempItem = new QGraphicsLineItem(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().rx(), event->scenePos().ry());
        this->addItem(tempItem);
        break;
    case DrawingState::RectZero:{
        //qDebug()<<"RectZero";
        //this->removeItem(tempItem);
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
        //qDebug()<<"CircleZero";
        //this->removeItem(tempItem);
        delete tempItem;
        auto min_x = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto min_y = min(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        auto max_x = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).rx(), event->scenePos().rx());
        auto max_y = max(event->buttonDownScenePos(Qt::MouseButton::LeftButton).ry(), event->scenePos().ry());
        //qDebug()<<min_x<<' '<<min_y<<" -- "<<max_x<<' '<<max_y;
        tempItem = new QGraphicsEllipseItem(QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y)));
        this->addItem(tempItem);
        break;
    }
    default:
        break;
    }

}

void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    //qDebug()<<"Mouse released";
    if(currentDrawingState==DrawingState::LineZero || currentDrawingState==DrawingState::RectZero || currentDrawingState==DrawingState::CircleZero){
        tempItem = nullptr;
        //currentDrawingState = DrawingState::Default;
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
    //qDebug()<<"Add Line";
    this->currentDrawingState = DrawingState::LineZero;
}

void MyGraphicsScene::addCircle() Q_SLOT{
    //qDebug()<<"Add Circle";
    this->currentDrawingState = DrawingState::CircleZero;
}

void MyGraphicsScene::addRect() Q_SLOT{
    //qDebug()<<"Add Rect";
    this->currentDrawingState = DrawingState::RectZero;
}

void MyGraphicsScene::removeSelected(){
    for(auto i:selectedItems){
        delete i;
    }
    selectedItems = QList<QGraphicsItem*>();
}
