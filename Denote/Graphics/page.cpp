#include "Graphics/page.h"
#include "pageportal.h"
#include <QPainter>
#include "Framework/pageitem.h"
#include "Framework/penstroke.h"
#include "Tools/pen.h"


Page::Page(){

}


void Page::setPageSize(int width, int height)
{
    this->width = width;
    this->height = height;
    setSceneRect(getPageBounds());
    foreach(PagePortal* portal, portals){
        portal->updateRenderArea();
    }
    updatePortals();
}


void Page::drawBackground(QPainter *painter, const QRectF &rect){
    Q_UNUSED(rect);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(white_page.active()));
    painter->drawRect(getPageBounds());

    if(page_type == Lines) paintLines(painter);
    else if(page_type == LinesMargin) paintLinesMargin(painter);
    else if(page_type == Engineering) paintEngineering(painter);
    else if(page_type == Graph) paintGraph(painter);
    else if(page_type == Staves) paintStaves(painter);
    else if(page_type == Custom) paintEngineering(painter);
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


void Page::setDisplayMode(IColor::DisplayMode display_mode)
{
    blue_line.setDisplayMode(display_mode);
    red_line.setDisplayMode(display_mode);
    border_green_line.setDisplayMode(display_mode);
    major_green_line.setDisplayMode(display_mode);
    minor_green_line.setDisplayMode(display_mode);
    alpha_black.setDisplayMode(display_mode);
    white_page.setDisplayMode(display_mode);
}


void Page::serializeRead(QDataStream &in)
{
    in >> width;
    in >> height;
    in >> work_area;
    in >> page_type;
    setPageSize(width,height);

    size_t num_items;
    in >> num_items;


    /*
    for(size_t i = 0; i < num_items; i++){
        ItemType type;
        in >> type;
        PageItem* new_item;
        if(type == ItemType::TypePenStroke) new_item = new PenStroke(in);
        else continue;
        addItem(new_item);
    }
    */
    update();
}


void Page::serializeWrite(QDataStream &out)
{
    out << width;
    out << height;
    out << work_area;
    out << page_type;
    size_t num_items = 0;
    foreach(QGraphicsItem* item, items()){
        PageItem* page_item = static_cast<PageItem*>(item);
        if(page_item != nullptr) num_items++;
    }
    out << num_items;
    foreach(QGraphicsItem* item, items()){
        PageItem* page_item = static_cast<PageItem*>(item);
        if(page_item != nullptr){
            out << page_item->type();
            page_item->serializeWrite(out);
        }
    }
}


void Page::findLowestObject()
{
    int y = 0;
    lowest_object = nullptr;
    foreach(QGraphicsItem* item, items()){
        if(item->isEnabled() and (lowest_object == nullptr or item->sceneBoundingRect().bottom() > y)){
            y = item->sceneBoundingRect().bottom();
            lowest_object = item;
        }
    }
}


void Page::updateLowestObject(QGraphicsItem *potential_lowest)
{
    if(potential_lowest->scene() != this or !potential_lowest->isEnabled()) return;

    if(potential_lowest->sceneBoundingRect().bottom() > getLowestPoint()){
        lowest_object = potential_lowest;
    }
}


int Page::getLowestPoint()
{
    if(lowest_object == nullptr) return 0;
    return lowest_object->sceneBoundingRect().bottom();
}


void Page::paintLines(QPainter *painter){
    painter->setPen(QPen(blue_line.active(),2));

    const int spacing = 28;
    const int margin = 40;

    for(int line = margin; line < height-margin; line += spacing){
        painter->drawLine(QLineF(0,line,width,line));
    }

    work_area = QRect(0,margin,width,height-2*margin);
}


void Page::paintLinesMargin(QPainter *painter){
    paintLines(painter);
    painter->setPen(QPen(red_line.active(),2));
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

    painter->setPen(QPen(border_green_line.active(),2));
    painter->drawLine(QLineF(left,top,left,bottom));//left margin
    painter->drawLine(QLineF(right,top,right,bottom));//right margin
    painter->drawLine(QLineF(0,top,width,top));//top margin
    painter->drawLine(QLineF(width*6/17,0,width*6/17, top));//title left
    painter->drawLine(QLineF(width*11/17,0,width*11/17, top));//title right

    painter->setPen(QPen(major_green_line.active(),2));
    for(int i = 0; i <= v_majors; i ++){//major horizontal lines
        painter->drawLine(QLineF(left,top+i*major_size,right,top+i*major_size));
    }
    for(int i = 0; i < h_majors; i ++){//major vertical lines
        painter->drawLine(QLineF(left+i*major_size,top,left+i*major_size,bottom));
    }

    painter->setPen(QPen(minor_green_line.active(),1));
    for(int i = 0; i < v_majors*major_minor; i ++){//minor horizontal lines
        if(i%major_minor) painter->drawLine(QLineF(left,top+i*minor_size,right,top+i*minor_size));
    }
    for(int i = 0; i < h_majors*major_minor; i ++){//minor vertical lines
        if(i%major_minor) painter->drawLine(QLineF(left+i*minor_size,top,left+i*minor_size,bottom));
    }

    work_area = QRect(0,top,width,bottom-top);
}


void Page::paintGraph(QPainter *painter){
    int grid_size = 20;

    painter->setPen(QPen(alpha_black.active(),1));

    for(int i = 0; i < width; i += grid_size){//vertical lines
        painter->drawLine(QLineF(i,0,i,height));
    }
    for(int i = 0; i < height; i += grid_size){//horizontal lines
        painter->drawLine(QLineF(0,i,width,i));
    }

    work_area = QRect(0,0,width,height);
}


void Page::paintStaves(QPainter *painter){
    int line_spacing = 12;
    int stave_spacing = 40;

    painter->setPen(QPen(alpha_black.active(),1));

    for(int i = 2*stave_spacing; i < height-5*line_spacing-stave_spacing; i+= 5*line_spacing+stave_spacing){
        for(int j = 0; j < 5; j++){
            painter->drawLine(QLineF(0.08*width, i+j*line_spacing,0.92*width, i+j*line_spacing));
        }
    }

    work_area = QRect(0,stave_spacing,width,height-2*stave_spacing);
}


void Page::paintCustom(QPainter *painter){
    Q_UNUSED(painter);
    return;
}
