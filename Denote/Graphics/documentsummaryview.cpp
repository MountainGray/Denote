#include "documentsummaryview.h"
#include "Framework/document.h"
#include "pagelayoutscene.h"
#include "Tools/tool.h"
#include "Ui/ui.h"


DocumentSummaryView::DocumentSummaryView(Document* doc)
{
    this->doc = doc;
    page_layout_scene = new PageLayoutScene(this, doc);
    setScene(page_layout_scene);

    doc->getUI()->setActiveLayout(page_layout_scene);

    setInteractive(false);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setTabletTracking(true);
    setMouseTracking(true);

    setBackgroundBrush(QBrush(QColor(37,37,40)));
}


void DocumentSummaryView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    fitInView(0,0,page_layout_scene->width()+x_padding,10,Qt::AspectRatioMode::KeepAspectRatio);
}


void DocumentSummaryView::enterEvent(QEnterEvent *event)
{
    doc->getUI()->setActiveLayout(page_layout_scene);
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}


void DocumentSummaryView::leaveEvent(QEvent *event)
{
    doc->getUI()->getActiveTool()->documentProximityEvent(event);
}
