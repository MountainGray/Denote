#include "document.h"
#include "Graphics/page.h"
#include "Ui/ui.h"

Document::Document(UI* ui, QObject* parent):QGraphicsScene(parent){
    this->ui = ui;
}


Document::~Document(){

}


void Document::addPage(Page *page){
    addItem(page);
    page->setY(pages.length()*(page->getHeight()+50));
    pages.append(page);
}


bool Document::removePage(int i){
    if(i < pages.length()){
        pages.removeAt(i);
        return true;
    } else return false;
}


void Document::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, QBrush(Qt::black));
    return;
    painter->drawPixmap(QPoint(0,0), background);
    painter->drawPixmap(QPoint(0,background.height()+50), background); //page 2
}

/*
void Document::mousePressEvent(QGraphicsSceneMouseEvent *event){
    ui->mousePressEvent(event);
    qDebug() << "Mouse Press" << event->scenePos();
}

void Document::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   ui->mouseMoveEvent(event);
   qDebug() << "Mouse Move Document" << event->scenePos();
}

void Document::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ui->mouseReleaseEvent(event);
    qDebug() << "Mouse Release" << event->scenePos();
}
*/
/*
bool Document::event(QEvent *event){
    if (event->type() == QEvent::TabletEnterProximity ||
        event->type() == QEvent::TabletLeaveProximity) {
        //ui->setTabletDevice(static_cast<QTabletEvent *>(event));
        return true;
    } else if(event->type() == QEvent::TabletPress){
        ui->tabletPress(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Press";
        event->accept();
        return true;
    } else if(event->type() == QEvent::TabletMove){
        ui->tabletMove(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Move";
        event->accept();
        return true;
    } else if(event->type() == QEvent::TabletRelease){
        ui->tabletRelease(static_cast<QTabletEvent *>(event));
        qDebug() << "Tablet Release";
        event->accept();
        return true;
    }
    return true;
}
*/
