#include "drawevent.h"
#include "documentgraphics.h"

DrawEvent::DrawEvent(QMouseEvent *event, DocumentGraphics* view) :
    QTabletEvent(event->type(),
                 event->pointingDevice(),
                 QPointF(float(event->position().x()), float(event->position().y())),
                 event->globalPosition(),
                 0.5, //pressure
                 0, //x_tilt
                 0, //y_tilt
                 0, //tangential_pressure
                 0, //rotation
                 0, //z
                 event->modifiers(),
                 event->button(),
                 event->buttons())
{
    doc_position = view->getInverse().map(event->position());
}


DrawEvent::DrawEvent(QTabletEvent *event, DocumentGraphics* view) : QTabletEvent(*event)
{
    doc_position = view->getInverse().map(event->position());
}
