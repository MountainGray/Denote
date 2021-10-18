#include "pageportal.h"
#include "page.h"
#include "pagelayoutscene.h"

#include <QPainter>
#include <QGraphicsView>
#include <QStyleOptionGraphicsItem>


PagePortal::PagePortal(Page* page, PageLayoutScene* page_layout, int index)
{
    this->page = page;
    this->page_layout = page_layout;

    page->portals.append(this);
    page_layout->portals.insert(index, this);
    page_layout->addItem(this);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
    setFlag(GraphicsItemFlag::ItemUsesExtendedStyleOption, true);

    //setCacheMode(DeviceCoordinateCache);

    updateRenderArea();
}


PagePortal::~PagePortal()
{
    page->portals.removeAll(this);
    page_layout->portals.removeAll(this);
    page_layout->removeItem(this);
    if(page_layout->focused_portal == this){
        page_layout->focused_portal = nullptr;
    }
}


QRectF PagePortal::scenePageBoundingRect()
{
    return mapRectToScene(render_to);
}


void PagePortal::updateRenderArea()
{
    if(page_layout->getLayoutType() == PageLayoutScene::Seamless){
        render_from = page->getWorkArea();
        render_to = QRectF(0,0,render_from.width(),render_from.height());
        page_offset = render_from.topLeft();
    } else {
        render_from = page->getPageBounds();
        render_to = render_from;
        page_offset = QPointF(0,0);
    }

    if(page_layout->hasShadow()){
        bounds = render_to.adjusted(0,0,SHADOW,SHADOW);
    } else {
        bounds = render_to;
    }
    qDebug() << "updating render area and calling update())";
    update();
}


void PagePortal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    //return;

    //qDebug() << "printing page portal" << option->exposedRect;

    anti = true;
    painter->setRenderHint(QPainter::Antialiasing,anti);
    anti = false;

    painter->setRenderHint(QPainter::SmoothPixmapTransform);


    painter->setBrush(Qt::NoBrush);
    QPen pen = QPen(QColor("black"),1,Qt::SolidLine,Qt::SquareCap, Qt::MiterJoin);


    if(page_layout->hasShadow()){
        for(int i = 0; i <= SHADOW; i ++){
            pen.setColor(QColor(0,0,0,std::min(i*17+15,255)));
            painter->setPen(pen);
            painter->drawRect(SHADOW+i, SHADOW+i, render_to.width()-2*i, render_to.height()-2*i);
        }
    }


    //painter->drawPixmap(option->exposedRect.adjusted(-2,-2,2,2), page->getCached(), option->exposedRect.adjusted(-2,-2,2,2));
    page->render(painter, render_to, render_from);
    //page->render(painter, option->exposedRect, option->exposedRect);
    //qDebug() << option->exposedRect;


    if(page_layout->hasHoles() and not page_layout->getDoc()->isEndless()){
        float hole_x = 26;
        float hole_size = 27;

        painter->setPen(Qt::NoPen);

        if(page_layout->hasShadow()){
            QLinearGradient grad = QLinearGradient(hole_x-2,0,hole_x+hole_size,0);
            grad.setColorAt(0,PageLayoutScene::BACKGROUND);
            grad.setColorAt(0.4,QColor(0,0,0));
            grad.setColorAt(1,QColor(0,0,0));
            painter->setBrush(QBrush(grad));
        } else {
            painter->setBrush(QBrush(PageLayoutScene::BACKGROUND));
        }

        int height = page->getHeight();
        int offset = page_offset.y();

        painter->drawEllipse(hole_x, 0.12*height-offset, hole_size, hole_size);
        painter->drawEllipse(hole_x, 0.5*height-offset, hole_size, hole_size);
        painter->drawEllipse(hole_x, 0.88*height-offset, hole_size, hole_size);
    }

    if(isSelected()){
        QPen pen = QPen(QColor(120,190,255),4);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(page->getPageBounds());
    }
}


