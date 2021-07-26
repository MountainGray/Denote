#include "documentsummaryview.h"
#include "Framework/document.h"
#include "pagelayoutscene.h"
#include "Tools/tool.h"
#include "Graphics/pageportal.h"
#include "Ui/ui.h"

#include <QtOpenGLWidgets/QOpenGLWidget>


DocumentSummaryView::DocumentSummaryView(Document* doc)
{
    setInteractive(false);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    resetGL();

    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

    setBackgroundBrush(QBrush(QColor(20,23,23)));

    this->doc = doc;
    page_layout_scene = new PageLayoutScene(this,doc);
    setScene(page_layout_scene);
    page_layout_scene->updatePageLayout();
    doc->getUI()->setActiveLayout(page_layout_scene);
}


DocumentSummaryView::~DocumentSummaryView()
{
    delete page_layout_scene;
}


void DocumentSummaryView::resetGL()
{
    QOpenGLWidget* gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(6);
    gl->setFormat(format);
    setViewport(gl);
    //should need to exist. Antialiasing missing when popping in/out subwindow.
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
    if(doc != nullptr){
        fitInView(0,0,page_layout_scene->width()+x_padding,10,Qt::AspectRatioMode::KeepAspectRatio);
    }
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
