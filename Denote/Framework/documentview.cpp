#include "documentview.h"

#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/documentinteractionframe.h"
#include "Ui/ui.h"

#include <QtOpenGLWidgets/QOpenGLWidget>


DocumentView::DocumentView(Document* doc)
{
    this->doc = doc;
    page_layout_scene = new PageLayoutScene(doc, this);
    setScene(page_layout_scene);
    doc->getUI()->setActiveLayout(page_layout_scene);

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);

    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    QOpenGLWidget* gl = new QOpenGLWidget();
    QSurfaceFormat format;
    format.setSamples(6);
    gl->setFormat(format);
    setViewport(gl);

    centerOn(0,0);

    setBackgroundBrush(QBrush(PageLayoutScene::BACKGROUND));
    doc->updateEndlessLength();
    page_layout_scene->updatePageLayout();

    setResizeAnchor(ViewportAnchor::AnchorViewCenter);
}


DocumentView::~DocumentView()
{
    delete page_layout_scene;
}


void DocumentView::setScale(float new_scale)
{
    float scale_factor = new_scale / view_scale;
    scale(scale_factor, scale_factor);
    view_scale = new_scale;
    doc->updateAllLayouts();
    doc->updateEndlessLength();
}


void DocumentView::scaleBy(float scale_factor)
{
    scale(scale_factor, scale_factor);
    view_scale *= scale_factor;
    doc->updateAllLayouts();
    doc->updateEndlessLength();
}


void DocumentView::focusDoc()
{
    if(doc->getUI()->getActiveDocument() != doc) doc->focusDoc();
}


void DocumentView::scaleToFit()
{
    fitInView(0,0,page_layout_scene->width()+view_padding,10,Qt::AspectRatioMode::KeepAspectRatio);
}
