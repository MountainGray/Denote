#include "Framework/documentgraphics.h"
#include "Framework/document.h"
#include "Framework/documentview.h"
#include "Tools/tool.h"
#include "drawevent.h"


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
        doc->getUI()->getTool()->drawPressEvent(DrawEvent(event, this));
    } else if(event->type() == QEvent::TabletMove){
        doc->getUI()->getTool()->drawMoveEvent(DrawEvent(event, this));
    } else if(event->type() == QEvent::TabletRelease){
        doc->getUI()->getTool()->drawReleaseEvent(DrawEvent(event, this));
    }
}


void DocumentGraphics::mousePressEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getTool()->drawPressEvent(DrawEvent(event, this));
    }
    QGraphicsView::mousePressEvent(event);
}


void DocumentGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getTool()->drawMoveEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseMoveEvent(event);
}


void DocumentGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getTool()->drawReleaseEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseReleaseEvent(event);//for zooming
}


void DocumentGraphics::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getTool()->drawDoubleClickEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseDoubleClickEvent(event);//for zooming
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
