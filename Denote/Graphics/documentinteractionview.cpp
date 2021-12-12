#include "documentinteractionview.h"
#include "pagelayoutscene.h"
#include "Framework/document.h"
#include "Tools/tool.h"
#include "Ui/ui.h"
#include "Framework/toolevent.h"
#include "Graphics/pageportal.h"
#include "Framework/History/historymanager.h"
#include "Graphics/page.h"
#include "mainwindow.h"
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
}


DocumentInteractionView::~DocumentInteractionView()
{

}


/*
void DocumentInteractionView::enterEvent(QEnterEvent *event)
{
    qDebug() << "Enter Event" << event->type();
    doc->getUI()->setActiveLayout(page_layout_scene);
    view_inverse = viewportTransform().inverted();
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
    event->accept();
}


void DocumentInteractionView::leaveEvent(QEvent *event)
{
    qDebug() << "Leave Event" << event->type();
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
    event->accept();
}
*/

void DocumentInteractionView::tabletEvent(QTabletEvent *event)
{
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
    if(event->deviceType() != QInputDevice::DeviceType::Mouse) return; //prevents artificial mouse events from stylus
    //qDebug() << "Mouse Press Event" << event->type();

    if(event->buttons() & Qt::MiddleButton){
        pan_offset = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }

    foreach(PagePortal* portal, page_layout_scene->getPortals()){
        if(portal->isUnderMouse()){
            page_layout_scene->setFocusedPortal(portal);
            doc->getUI()->setActivePage(portal->getPage());
            doc->getUI()->setActivePortal(portal);
            page_inverse = portal->getPageOffset() - portal->scenePos();
        }
    }
    //setGL(false);
    doc->getUI()->getActiveTool()->drawPressEvent(ToolEvent(event, this));
    focusDoc();
}


void DocumentInteractionView::mouseMoveEvent(QMouseEvent *event)
{

    //qDebug() << event->isAccepted() << "Mouse Move Event" << event->type() << event->source() << event->deviceType() << event->pos();

    if(event->deviceType() != QInputDevice::DeviceType::Mouse) return; //prevents artificial mouse events from stylus

    //qDebug() << "Mouse Move Event" << event->type() << event->source();

    if(event->buttons() & Qt::MiddleButton){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - pan_offset.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - pan_offset.y()));
        pan_offset = event->position();
        view_inverse = viewportTransform().inverted();

    } else {
        doc->getUI()->getActiveTool()->setView(this);
        doc->getUI()->getActiveTool()->drawMoveEvent(ToolEvent(event, this));
    }

    QGraphicsView::mouseMoveEvent(event);//to set mouse anchor for zoom events
}


void DocumentInteractionView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->deviceType() != QInputDevice::DeviceType::Mouse) return; //prevents artificial mouse events from stylus

    if(event->button() == Qt::MiddleButton){
        //qDebug() << "middle release";
        //doc->getUI()->getActivePortal()->setAnti();
        //doc->getUI()->getActivePortal()->update();
        return;
    }

    //qDebug() << "Mouse Release Event" << event->type();
    setCursor(Qt::ArrowCursor);
    doc->getUI()->getActiveTool()->drawReleaseEvent(ToolEvent(event, this));
    //setGL(true);
}

/*
void DocumentInteractionView::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
    if(event->deviceType() != QInputDevice::DeviceType::Mouse) return; //prevents artificial mouse events from stylus

    qDebug() << "Mouse Double Click Event" << event->type();
    doc->getUI()->getActiveTool()->drawDoubleClickEvent(ToolEvent(event, this));
}
*/

void DocumentInteractionView::wheelEvent(QWheelEvent *event){

    qDebug() << "Wheel Event" << event->type();
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
            frame->updateScaleSlider();
        }
        event->accept();
    } else {
        if(page_layout_scene->getLayoutType() == PageLayoutScene::Horizontal){
            horizontalScrollBar()->setValue(horizontalScrollBar()->value()-event->angleDelta().y());
        } else {
            QGraphicsView::wheelEvent(event);
        }
    }
    view_inverse = viewportTransform().inverted();
    event->accept();
}

void DocumentInteractionView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Space){
        doc->getUI()->getActivePortal()->setRotation(doc->getUI()->getActivePortal()->rotation()+15);
    } else if (event->key() == Qt::Key::Key_D){
        foreach(QGraphicsItem* item, scene()->items()){
            scene()->removeItem(item);
        }
    } else if (event->key() == Qt::Key::Key_C){
        doc->getUI()->getActivePage()->cache();
    }
}
/*

bool DocumentInteractionView::event(QEvent *event)
{
    //no need to accept or ignore events in here, just return true/false

    return false;//stop and don't propogate event to parents

    if(event->type() == QEvent::TouchBegin or
       event->type() == QEvent::TouchCancel or
       event->type() == QEvent::TouchEnd or
       event->type() == QEvent::TouchUpdate){

        qDebug() << "Event" << event->type();

        QTouchEvent* touch_event = static_cast<QTouchEvent*>(event);
        if(touch_event == nullptr){
            qDebug() << "Touch event" << touch_event->point(0).globalPosition();
            return true;
        }
    }

    if(event->type() == QEvent::TabletMove){
        event->ignore();
        return false;
    }

    return true;
    //return QGraphicsView::event(event);
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
}
*/


void DocumentInteractionView::scrollPositionChanged()
{
    doc->updateEndlessLength();
}
