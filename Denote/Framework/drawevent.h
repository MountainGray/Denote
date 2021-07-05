#ifndef DRAWEVENT_H
#define DRAWEVENT_H

#include <QMouseEvent>
#include <QTabletEvent>

class DocumentGraphics;

class DrawEvent : public QTabletEvent
{
public:
    DrawEvent(QMouseEvent *event, DocumentGraphics* view);
    DrawEvent(QTabletEvent *event, DocumentGraphics* view);

public:
    QPointF docPos(){return doc_position;}

private:
    QPointF doc_position;
};

#endif // DRAWEVENT_H
