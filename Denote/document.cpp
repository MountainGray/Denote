#include "document.h"


Document::Document(){
    QString fileName = "C:/Users/Lewis/Documents/Classes/PDFs/Engi_Paper.png";
    background = QPixmap(fileName);
    background = background.scaledToWidth(1920,Qt::SmoothTransformation);
}


Document::~Document(){

}


void Document::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, QBrush(Qt::black));
    painter->drawPixmap(QPoint(0,0), background);
    painter->drawPixmap(QPoint(0,background.height()+50), background); //page 2
}
