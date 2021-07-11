#include "documentinteractionview.h"
#include "pagelayoutscene.h"
#include "Framework/document.h"
#include "Tools/tool.h"
#include "Ui/ui.h"
#include "Framework/toolevent.h"
#include "Graphics/pageportal.h"


DocumentInteractionView::DocumentInteractionView(Document* doc)
{
    this->doc = doc;
    page_layout_scene = new PageLayoutScene(this, doc);
    page_layout_scene->setAutoLayout(true);
    setScene(page_layout_scene);

    doc->getUI()->setActiveLayout(page_layout_scene);

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    centerOn(page_layout_scene->width()/2,0);

    setTabletTracking(true);
    setMouseTracking(true);

    //setBackgroundBrush(QBrush(QColor("black")));
    setBackgroundBrush(QBrush(QColor(37,37,40)));
}


void DocumentInteractionView::setScale(float view_scale)
{
    float new_scale = view_scale / transform().m11();
    scale(new_scale, new_scale);
}


void DocumentInteractionView::enterEvent(QEnterEvent *event)
{
    doc->getUI()->setActiveLayout(page_layout_scene);
    view_inverse = viewportTransform().inverted();
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}


void DocumentInteractionView::leaveEvent(QEvent *event)
{
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}


void DocumentInteractionView::tabletEvent(QTabletEvent *event){
    event->accept();

    if(event->type() == QEvent::TabletPress){
        foreach(PagePortal* portal, page_layout_scene->getPortals()){
            if(portal->isUnderMouse()){
                doc->getUI()->setActivePage(portal->getPage());
                page_inverse = -portal->scenePos();
            }
        }
        doc->getUI()->getActiveTool()->drawPressEvent(ToolEvent(event, this));
    } else if(event->type() == QEvent::TabletMove){
        doc->getUI()->getActiveTool()->drawMoveEvent(ToolEvent(event, this));
    } else if(event->type() == QEvent::TabletRelease){
        doc->getUI()->getActiveTool()->drawReleaseEvent(ToolEvent(event, this));
    }
}


void DocumentInteractionView::mousePressEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        foreach(PagePortal* portal, page_layout_scene->getPortals()){
            if(portal->isUnderMouse()){
                doc->getUI()->setActivePage(portal->getPage());
                page_inverse = -portal->scenePos();
            }
        }
        doc->getUI()->getActiveTool()->drawPressEvent(ToolEvent(event, this));
    }
}


void DocumentInteractionView::mouseMoveEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawMoveEvent(ToolEvent(event, this));
    }
    QGraphicsView::mouseMoveEvent(event);//for zoom
}


void DocumentInteractionView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawReleaseEvent(ToolEvent(event, this));
    }
}


void DocumentInteractionView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->deviceType() == QInputDevice::DeviceType::Mouse){//prevents artificial mouse events from stylus
        doc->getUI()->getActiveTool()->drawDoubleClickEvent(ToolEvent(event, this));
    }
}


void DocumentInteractionView::wheelEvent(QWheelEvent *event){
    if (event->modifiers() & Qt::ControlModifier){
        if(event->modifiers() & Qt::ShiftModifier){//rotate
            if (event->angleDelta().y() > 0)
                rotate(5);
            else
                rotate(-5);
        } else {//zoom
            if (event->angleDelta().y() > 0)
                scale(1.1,1.1);
            else
                scale(1/1.1,1/1.1);
        }
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
    view_inverse = viewportTransform().inverted();
}


void DocumentInteractionView::keyPressEvent(QKeyEvent *event)
{
    /*
    if(event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier){
        QClipboard *clip = QGuiApplication::clipboard();
        QImage image = clip->image(QClipboard::Clipboard);
        if(not image.isNull()){
            Image *new_image = new Image(doc->getUI());
            new_image->setImage(image);
        }
    } else if(event->key() == Qt::Key_Delete){
        foreach(QGraphicsItem *item, doc->selectedItems()){
            doc->removeItem(item);
            delete item;
        }
    } else if(event->key() == Qt::Key_D){
        foreach(QGraphicsItem *item, doc->selectedItems()){

            Stroke* stroke = static_cast<Stroke*>(item);
            if(stroke){
                stroke->setSelected(false);
                Stroke* new_stroke = new Stroke(stroke);
                new_stroke->moveBy(20,20);
                doc->addItem(new_stroke);
                new_stroke->setSelected(true);
            }

        }
        doc->getUI()->setActiveTool(doc->getUI()->getActiveTool());
    }
    */
}
