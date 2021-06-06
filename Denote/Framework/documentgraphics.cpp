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
        e->accept();
    } else {
        QGraphicsView::wheelEvent(e);
    }
}

/*
void DocumentGraphics::tabletEvent(QTabletEvent *event){
    event->setAccepted(true);
    if (event->type() == QEvent::TabletEnterProximity ||
        event->type() == QEvent::TabletLeaveProximity) {
        //ui->setTabletDevice(static_cast<QTabletEvent *>(event));
    } else if(event->type() == QEvent::TabletPress){
        //ui->tabletPress(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Press";
        event->accept();
    } else if(event->type() == QEvent::TabletMove){
        //ui->tabletMove(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Move";
        event->accept();
    } else if(event->type() == QEvent::TabletRelease){
        //ui->tabletRelease(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Release";
        event->accept();
    }
    //QWidget::tabletEvent(event);
    event->accept();
}

void DocumentGraphics::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Press";
    event->accept();
}

void DocumentGraphics::mouseMoveEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::MouseMove){
        qDebug() << "Mouse Move";
        event->accept();
    }
}

void DocumentGraphics::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Mouse Release";
    event->accept();
}
*/

