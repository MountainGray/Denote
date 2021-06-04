#include "documentgraphics.h"
#include "document.h"
#include "documentview.h"


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

