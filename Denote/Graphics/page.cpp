#include "Graphics/page.h"
#include "pageportal.h"
#include <QPainter>


Page::Page() : QGraphicsScene(){
    setPageSize(850,1100);
}


void Page::setPageSize(int width, int height)
{
    this->width = width;
    this->height = height;
    setSceneRect(QRect(0,0,width,height));
}


void Page::drawBackground(QPainter *painter, const QRectF &rect){
    painter->setPen(QPen(QColor("white"),2));
    painter->setBrush(QBrush(QColor("white")));
    painter->drawRect(QRect(0,0,width,height));

    if(page_type == Lines) paintLines(painter);
    else if(page_type == LinesMargin) paintLinesMargin(painter);
    else if(page_type == Engineering) paintEngineering(painter);
    else if(page_type == Graph) paintGraph(painter);
    else if(page_type == Staves) paintStaves(painter);
    else if(page_type == Custom) paintEngineering(painter);
    else paintEngineering(painter);

    painter->setPen(QPen(QColor("black"),2));
    painter->setBrush(QBrush(QColor("black")));

    float hole_x = 26;
    float hole_size = 27;

    painter->drawEllipse(hole_x, 0.12*height, hole_size, hole_size);
    painter->drawEllipse(hole_x, 0.5*height, hole_size, hole_size);
    painter->drawEllipse(hole_x, 0.88*height, hole_size, hole_size);


}


void Page::addPortal(PagePortal *portal)
{
    portals.append(portal);
}


void Page::removePortal(PagePortal *portal)
{
    portals.remove(portals.indexOf(portal));
}


void Page::updatePortals(QRectF rect)
{
    foreach(PagePortal* portal, portals){
        if(rect.isEmpty()){
            portal->update();
        } else {
            portal->update(rect);
        }
    }
}


void Page::paintLines(QPainter *painter){
    painter->setPen(QPen(QColor(43,167,255,150),2));
    for(int line = height/10; line < 20*height/21; line += height/40){
        painter->drawLine(QLineF(0,line,width,line));
    }
}


void Page::paintLinesMargin(QPainter *painter){
    paintLines(painter);
    painter->setPen(QPen(QColor(255,50,43,150),2));
    painter->drawLine(QLineF(width/8,0,width/8,height));
}


void Page::paintEngineering(QPainter *painter){
    int minor_size = 20;//in pixels
    int major_minor = 5;
    int major_size = minor_size*major_minor;

    float h_majors = (width/major_size)-1;
    float v_majors = (height/major_size)-1;
    float h_excess = width - (h_majors*major_size);
    float v_excess = height - (v_majors*major_size);

    float left = 0.6*h_excess;
    float right = width - 0.4*h_excess;
    float top = v_excess/2;
    float bottom = height-v_excess/2;

    painter->setPen(QPen(QColor(56,171,87,255),2));
    painter->drawLine(QLineF(left,top,left,bottom));//left margin
    painter->drawLine(QLineF(right,top,right,bottom));//right margin
    painter->drawLine(QLineF(0,top,width,top));//top margin
    painter->drawLine(QLineF(width*6/17,0,width*6/17, top));//title left
    painter->drawLine(QLineF(width*11/17,0,width*11/17, top));//title right

    painter->setPen(QPen(QColor(56,171,87,100),2));
    for(int i = 0; i <= v_majors; i ++){//major horizontal lines
        painter->drawLine(QLineF(left,top+i*major_size,right,top+i*major_size));
    }
    for(int i = 0; i < h_majors; i ++){//major vertical lines
        painter->drawLine(QLineF(left+i*major_size,top,left+i*major_size,bottom));
    }

    painter->setPen(QPen(QColor(56,171,87,100),1));
    for(int i = 0; i < v_majors*major_minor; i ++){//minor horizontal lines
        if(i%major_minor) painter->drawLine(QLineF(left,top+i*minor_size,right,top+i*minor_size));
    }
    for(int i = 0; i < h_majors*major_minor; i ++){//minor vertical lines
        if(i%major_minor) painter->drawLine(QLineF(left+i*minor_size,top,left+i*minor_size,bottom));
    }
}


void Page::paintGraph(QPainter *painter){
    int grid_size = 20;

    painter->setPen(QPen(QColor(0,0,0,125),1));

    for(int i = 0; i < width; i += grid_size){//vertical lines
        painter->drawLine(QLineF(i,0,i,height));
    }
    for(int i = 0; i < height; i += grid_size){//horizontal lines
        painter->drawLine(QLineF(0,i,width,i));
    }
}


void Page::paintStaves(QPainter *painter){
    int line_spacing = 12;
    int stave_spacing = 40;

    painter->setPen(QPen(QColor(0,0,0,125),1));

    for(int i = 2*stave_spacing; i < height-5*line_spacing-stave_spacing; i+= 5*line_spacing+stave_spacing){
        for(int j = 0; j < 5; j++){
            painter->drawLine(QLineF(0.08*width, i+j*line_spacing,0.92*width, i+j*line_spacing));
        }
    }
}


void Page::paintCustom(QPainter *painter){
    Q_UNUSED(painter);
    return;
}
