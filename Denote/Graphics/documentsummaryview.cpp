#include "documentsummaryview.h"
#include "Framework/document.h"
#include "pagelayoutscene.h"
#include "Tools/tool.h"
#include "Graphics/pageportal.h"
#include "Ui/ui.h"


DocumentSummaryView::DocumentSummaryView(Document* doc)
{
    this->doc = doc;
    page_layout_scene = new PageLayoutScene(this, doc);
    setScene(page_layout_scene);

    page_layout_scene->updatePageLayout();

    doc->getUI()->setActiveLayout(page_layout_scene);

    setInteractive(false);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setBackgroundBrush(QBrush(QColor(37,37,40)));
}


void DocumentSummaryView::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    foreach(PagePortal* portal, page_layout_scene->getPortals()){
        portal->setSelected(portal->isUnderMouse());
    }
}


void DocumentSummaryView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    fitInView(0,0,page_layout_scene->width()+x_padding,10,Qt::AspectRatioMode::KeepAspectRatio);
}


void DocumentSummaryView::keyPressEvent(QKeyEvent *event)
{
    foreach(PagePortal* portal, page_layout_scene->getPortals()){
        if(portal->isSelected()){
            doc->removePage(portal->getPage());
        }
    }
}
