#include "toolpreset.h"

#include "Tools/tool.h"
#include "Ui/ui.h"

ToolPreset::ToolPreset(Tool* tool)
{
    this->tool = tool;
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedSize(60,60);
}


void ToolPreset::paintEvent(QPaintEvent *event)
{
    tool->paintPreset(event);
}


void ToolPreset::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        tool->getUI()->setActiveTool(tool);
    }
}
