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

