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

    page_layout_scene->updatePageLayout();

    doc->getUI()->setActiveLayout(page_layout_scene);

    setInteractive(false);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setBackgroundBrush(QBrush(QColor(37,37,40)));
}


void DocumentSummaryView::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    fitInView(0,0,page_layout_scene->width()+x_padding,10,Qt::AspectRatioMode::KeepAspectRatio);
}
