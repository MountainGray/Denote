#include "Framework/documentgraphics.h"
#include "Framework/document.h"
#include "Framework/documentview.h"


DocumentGraphics::DocumentGraphics(DocumentView *view, Document *doc) : QGraphicsView(view){
    this->doc = doc;
    setScene(doc);
    setSceneRect(0,0,850, 3*1150);

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);
}


void DocumentGraphics::tabletEvent(QTabletEvent *event){
    event->accept();

    if (event->type() == QEvent::TabletEnterProximity ||
        event->type() == QEvent::TabletLeaveProximity) {
        //update cursor to specific writing cursor (if for tablet only)
    } else if(event->type() == QEvent::TabletPress){
        doc->getUI()->tabletPressEvent(mapToDoc(event));
    } else if(event->type() == QEvent::TabletMove){
        doc->getUI()->tabletMoveEvent(mapToDoc(event));
    } else if(event->type() == QEvent::TabletRelease){
        doc->getUI()->tabletReleaseEvent(mapToDoc(event));
    }
}


void DocumentGraphics::mousePressEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        QGraphicsView::mousePressEvent(event);//prevents artificial mouse events from stylus
    }
}


void DocumentGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        QGraphicsView::mouseMoveEvent(event);//prevents artificial mouse events from stylus
    }
}


void DocumentGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        QGraphicsView::mouseReleaseEvent(event);//prevents artificial mouse events from stylus
    }
}


void DocumentGraphics::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){
        QGraphicsView::mouseDoubleClickEvent(event);//prevents artificial mouse events from stylus
    }
}


void DocumentGraphics::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier){
        if(e->modifiers() & Qt::ShiftModifier){//rotate
            if (e->angleDelta().y() > 0)
                rotation += 5;
            else
                rotation -= 5;
        } else {//zoom
            if (e->angleDelta().y() > 0)
                scale *= 1.1;
            else
                scale /= 1.1;
        }
        QTransform matrix;
        matrix.scale(scale, scale);
        matrix.rotate(rotation);
        setTransform(matrix);
        //might just use scale() and rotate() instead -------
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}


QTabletEvent *DocumentGraphics::mapToDoc(QTabletEvent *event)
{
    //not sure if this should be deleted manually, possible memory leak
    return new QTabletEvent(event->type(),
                        event->pointingDevice(),
                        viewportTransform().inverted().map(event->position()), //only difference
                        event->globalPosition(),
                        event->pressure(),
                        event->xTilt(),
                        event->yTilt(),
                        event->tangentialPressure(),
                        event->rotation(),
                        event->z(),
                        event->modifiers(),
                        event->button(),
                        event->buttons());
}
