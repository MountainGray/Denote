#include "documentview.h"

#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Framework/penstroke.h"
#include "Framework/offscreenopengl.h"

#include <QScrollBar>
#include <QApplication>

DocumentView::DocumentView(Document* doc)
{
    this->doc = doc;
    page_layout_scene = new PageLayoutScene(doc, this);
    setScene(page_layout_scene);
    doc->getUI()->setActiveLayout(page_layout_scene);

    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);

    setInteractive(false);

    centerOn(0,0);

    doc->updateEndlessLength();
    page_layout_scene->updatePageLayout();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setBackgroundBrush(QBrush(PageLayoutScene::BACKGROUND));
    setStyleSheet(
        "QScrollBar:vertical {border: 1px; background: none; width: 7px; margin: 0px 1px 0px 1px;}"
        "QScrollBar::handle:vertical {background: #444444; min-height: 10px;}"
        "QScrollBar::add-page, QScrollBar::sub-page {background: none;}"
        "QScrollBar::add-line, QScrollBar::sub-line {background: none;}"
        "QScrollBar::up-arrow, QScrollBar::down-arrow {background: none;}");

    gl = new OffscreenOpenGL(viewport());

    connect(scene(), SIGNAL(changed(QList<QRectF>)), this, SLOT(updateScene(QList<QRectF>)));
}

DocumentView::~DocumentView()
{
    delete page_layout_scene;
}


void DocumentView::paintEvent(QPaintEvent *event)
{

    if(normal){
        QGraphicsView::paintEvent(event);
        normal = false;
        return;
    }


    if(image->isNull() || event->rect() == viewport()->rect()) cacheScene();

    QRect image_rect = QRect(event->rect().topLeft() * devicePixelRatio(), event->rect().bottomRight() * devicePixelRatio());
    QPainter wpainter(viewport());
    qDebug() << image_rect;
    wpainter.setRenderHints(QPainter::Antialiasing);//| QPainter::SmoothPixmapTransform);
    wpainter.drawImage(event->rect(), *image, image_rect);

    if(stroke != nullptr){ // partial update
        paintCachedStroke(&wpainter);
    }
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


void DocumentView::resizeEvent(QResizeEvent *event)
{
    page_layout_scene->updatePageLayout();
    QGraphicsView::resizeEvent(event);
    gl->resizeEvent(event);
    cacheScene();
}


void DocumentView::cacheScene(QRect rect)
{
    qDebug() << "Repainting Background via OpenGL";

    if(rect.isNull()) rect = viewport()->rect();

    QPainter gpainter(gl->paintDevice());

    gpainter.setRenderHints(QPainter::Antialiasing);// | QPainter::SmoothPixmapTransform);
    render(&gpainter, rect, rect);
    *image = gl->grabFramebuffer();
}


void DocumentView::clearCachedStroke()
{
    //flatten stroke onto image
    QPainter p(image);
    p.setRenderHint(QPainter::Antialiasing);
    paintCachedStroke(&p);

    this->stroke = nullptr;
}


void DocumentView::paintCachedStroke(QPainter* painter)
{
    if(stroke != nullptr){
        painter->save();

        QPointF offset = doc->getUI()->getActivePortal()->scenePos();
        QTransform t = viewportTransform();
        t.translate(offset.x(),offset.y());
        painter->setTransform(t);

        painter->setClipRect(doc->getUI()->getActivePortal()->getRenderTo());

        stroke->paint(painter, new QStyleOptionGraphicsItem());
        painter->restore();
    }
}



