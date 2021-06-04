#ifndef TOOL_H
#define TOOL_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>

// todo: add all event handling void methods
class Tool
{
public:
    Tool();

public:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    //virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0;
    //virtual void keyPressEvent(QKeyEvent *event) = 0;
    //virtual void wheelEvent(QGraphicsSceneWheelEvent *event) = 0;

};

#endif // TOOL_H
