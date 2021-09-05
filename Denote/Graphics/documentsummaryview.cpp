#include "documentsummaryview.h"


DocumentSummaryView::DocumentSummaryView(Document* doc) : DocumentView(doc)
{
    setInteractive(false);
    page_layout_scene->setInteractive(false);
    page_layout_scene->setLayoutType(PageLayoutScene::Vertical);
    page_layout_scene->setShadow(false);

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
}


DocumentSummaryView::~DocumentSummaryView()
{

}


void DocumentSummaryView::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(doc != nullptr){
        foreach(PagePortal* portal, page_layout_scene->getPortals()){
            portal->setSelected(portal->isUnderMouse());
        }
    }

}


void DocumentSummaryView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    scaleToFit();
}


void DocumentSummaryView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete and doc != nullptr){
        foreach(PagePortal* portal, page_layout_scene->getPortals()){
            if(portal->isSelected()){
                doc->removePage(portal->getPage());
            }
        }
    }
}
