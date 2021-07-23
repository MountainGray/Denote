#include "toollibrary.h"

#include "Tools/tool.h"
#include "Framework/toolpreset.h"

ToolLibrary::ToolLibrary(QMainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(200,100);
    setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

    library = new QWidget();
    setWidget(library);

    layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight, library);
    layout->setAlignment(Qt::AlignmentFlag::AlignLeft);
}


void ToolLibrary::addTool(Tool *tool)
{
    layout->addWidget(tool->toolPreset());
}


void ToolLibrary::setActiveTool(Tool *tool)
{
    active_preset = tool;
}
