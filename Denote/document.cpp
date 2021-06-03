#include "document.h"
#include "page.h"

Document::Document(){
    QString fileName = "C:/Users/Lewis/Documents/Classes/PDFs/Engi_Paper.png";
    background = QPixmap(fileName);
    background = background.scaledToWidth(1920,Qt::SmoothTransformation);
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
