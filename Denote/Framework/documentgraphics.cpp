#include "Framework/documentgraphics.h"
#include "Framework/document.h"
#include "Framework/documentview.h"
#include "Tools/tool.h"
#include "drawevent.h"


DocumentGraphics::DocumentGraphics(DocumentView *view, Document *doc) : QGraphicsView(view){
    this->doc = doc;
    setScene(doc);
    setSceneRect(0,0,850, 4*1150);

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    centerOn(doc->width()/2,0);

    setTabletTracking(true);
    setMouseTracking(true);
}


void DocumentGraphics::setScale(float view_scale)
{
    float new_scale = view_scale / transform().m11();
    scale(new_scale, new_scale);
}


void DocumentGraphics::enterEvent(QEnterEvent *event)
{
    doc->getUI()->setActiveView(this);
    inverse = viewportTransform().inverted();
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}


void DocumentGraphics::leaveEvent(QEvent *event)
{
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}


void DocumentGraphics::tabletEvent(QTabletEvent *event){
    event->accept();

    if(event->type() == QEvent::TabletPress){
        doc->getUI()->getActiveTool()->drawPressEvent(DrawEvent(event, this));
    } else if(event->type() == QEvent::TabletMove){
        doc->getUI()->getActiveTool()->drawMoveEvent(DrawEvent(event, this));
    } else if(event->type() == QEvent::TabletRelease){
        doc->getUI()->getActiveTool()->drawReleaseEvent(DrawEvent(event, this));
    }
}


void DocumentGraphics::mousePressEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawPressEvent(DrawEvent(event, this));
    }
    QGraphicsView::mousePressEvent(event);
}


void DocumentGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawMoveEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseMoveEvent(event);
}


void DocumentGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawReleaseEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseReleaseEvent(event);//for zooming
}


void DocumentGraphics::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawDoubleClickEvent(DrawEvent(event, this));
    }
    QGraphicsView::mouseDoubleClickEvent(event);//for zooming
}


void DocumentGraphics::wheelEvent(QWheelEvent *e){
    if (e->modifiers() & Qt::ControlModifier){
        if(e->modifiers() & Qt::ShiftModifier){//rotate
            if (e->angleDelta().y() > 0)
                rotate(5);
            else
                rotate(-5);
        } else {//zoom
            if (e->angleDelta().y() > 0)
                scale(1.1,1.1);
            else
                scale(1/1.1,1/1.1);
        }  
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
    inverse = viewportTransform().inverted();
}


void DocumentGraphics::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Space){
        doc->getUI()->switchTool();
    }
}
