#include "document.h"
#include "Framework/pagelayout.h"
#include "Ui/ui.h"
#include "Framework/documentgraphics.h"


Document::Document(UI* ui, QObject* parent):QGraphicsScene(parent){
    this->ui = ui;
    page_layout = new PageLayout(this);
}


Document::~Document(){

}


void Document::addPage(Page *page){
    addItem(page);
    pages.append(page);
    updatePages();
    updateSceneRect();
}


bool Document::removePage(int i){
    if(i < pages.length()){
        pages.removeAt(i);
        updatePages();
        updateSceneRect();
        return true;
    } else return false;
}


QRectF Document::getDocBounds()
{
    return page_layout->getBounds();
}


void Document::updateActivePage()
{
    foreach(Page* page, pages){
        if(page->isUnderMouse()){
            active_page = page;
        }
    }
}


void Document::removeItems(QList<QGraphicsItem *> items)
{
    foreach(QGraphicsItem* item, items){
        removeItem(item);
    }
}


void Document::updateSceneRect()
{
    foreach(QGraphicsView* graphics, ui->getGraphics()){
        graphics->setSceneRect(page_layout->getBounds());
    }
}


void Document::updatePages()
{
    page_layout->updatePositions();
}


void Document::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, QBrush(Qt::black));
}

