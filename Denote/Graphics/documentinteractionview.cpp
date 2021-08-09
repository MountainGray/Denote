#include "documentinteractionview.h"
#include "Framework/History/historymanagerviewer.h"
#include "Graphics/documentinteractionframe.h"
#include "Tools/image.h"

#include <QScrollBar>
#include <QClipboard>
#include <QGuiApplication>


DocumentInteractionView::DocumentInteractionView(Document* doc, DocumentInteractionFrame* frame) : DocumentView(doc)
{
    this->frame = frame;
    page_layout_scene->setLayoutType(PageLayoutScene::FitToView);
    connect(verticalScrollBar(), &QAbstractSlider::valueChanged, this, &DocumentInteractionView::scrollPositionChanged);
    frame->resetScale();
}


DocumentInteractionView::~DocumentInteractionView()
{

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
                page_layout_scene->setFocusedPortal(portal);
                doc->getUI()->setActivePage(portal->getPage());
                doc->getUI()->setActivePortal(portal);
                page_inverse = portal->getPageOffset() - portal->scenePos();
            }
        }
        doc->getUI()->getActiveTool()->drawPressEvent(ToolEvent(event, this));
        focusDoc();
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
                page_layout_scene->setFocusedPortal(portal);
                doc->getUI()->setActivePage(portal->getPage());
                doc->getUI()->setActivePortal(portal);
                page_inverse = portal->getPageOffset() - portal->scenePos();
            }
        }
        doc->getUI()->getActiveTool()->drawPressEvent(ToolEvent(event, this));
    }
    focusDoc();
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
            doc->updateAllLayouts();
            doc->updateEndlessLength();
        } else {//zoom
            if (event->angleDelta().y() > 0 and view_scale < 5){
                scaleBy(1.1);
            } else if(event->angleDelta().y() < 0 and view_scale > 0.2){
                scaleBy(1/1.1);
            }
            frame->resetScale();
        }
        event->accept();
    } else {
        QGraphicsView::wheelEvent(event);
    }
    view_inverse = viewportTransform().inverted();
}


void DocumentInteractionView::keyPressEvent(QKeyEvent *event)
{
    doc->getUI()->getHistoryManagerViewer()->keyPressEvent(event);
    doc->getUI()->getHistoryManagerViewer()->setHistoryManager(doc->getHistoryManager());

    if(event->key() == Qt::Key_V && event->modifiers() == Qt::ControlModifier){
        QClipboard *clip = QGuiApplication::clipboard();
        QImage image = clip->image(QClipboard::Clipboard);
        if(not image.isNull()){
            Image *new_image = new Image(doc->getUI());
            new_image->setImage(image);
        }
    }
    /*
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


void DocumentInteractionView::scrollPositionChanged()
{
    doc->updateEndlessLength();
}
