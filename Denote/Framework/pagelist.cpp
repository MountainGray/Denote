#include "Framework/pagelist.h"

#include "Framework/document.h"
#include "Framework/pagelistviewer.h"
#include "Graphics/page.h"

#include <QGuiApplication>


PageList::PageList(PageListViewer *view, Document *doc) : QGraphicsView(view){
    this->doc = doc;
    setScene(doc);
    setSceneRect(doc->getDocBounds());

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
}


void PageList::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    foreach(Page* page, doc->getPages()){
        if(page->isUnderMouse()){
            page->setSelected(true);
            selected_page = page;
        } else {
            page->setSelected(false);
        }
    }
}


void PageList::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete){

    } else if(event->key() == Qt::Key_Down){
        QList<Page*> pages = doc->getPages();
        int i = pages.indexOf(selected_page);
        if(i < pages.length()-1){
            pages.removeAt(i);
            pages.insert(i+1,selected_page);
            doc->setPages(pages);
            doc->updatePages();
        }
    } else if(event->key() == Qt::Key_Up){
        QList<Page*> pages = doc->getPages();
        int i = pages.indexOf(selected_page);
        if(i > 0){
            pages.removeAt(i);
            pages.insert(i-1,selected_page);
            doc->setPages(pages);
            doc->updatePages();
        }
    } else if(event->key() == Qt::Key_A){
        doc->addPage(new Page());
    }
}


void PageList::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    float new_scale = width() / float(doc->getDocBounds().width() + 20) / transform().m11();
    scale(new_scale, new_scale);
}

