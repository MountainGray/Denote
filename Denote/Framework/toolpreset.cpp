#include "toolpreset.h"

#include "Tools/tool.h"
#include "Ui/ui.h"
#include <QPainter>

ToolPreset::ToolPreset(Tool* tool)
{
    this->tool = tool;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(50,50);
}


void ToolPreset::paintEvent(QPaintEvent *event)
{
    tool->paintPreset(event);

    if(tool->getUI()->getActiveTool() == tool){
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(50,150,255), 3));
        painter.drawRect(QRectF(0,0,width(),height()));
    }
}


void ToolPreset::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        tool->getUI()->setActiveTool(tool);
    }
}
