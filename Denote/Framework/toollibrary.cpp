#include "toollibrary.h"
<<<<<<< Updated upstream
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
#include "Tools/tool.h"
#include "Framework/toolpreset.h"
#include "Framework/toolmenu.h"
#include "Framework/toolmenuviewer.h"
#include "Ui/ui.h"

#include "Tools/pen.h"
#include "Tools/fill.h"
#include "Tools/eraser.h"
#include "Tools/selectionbox.h"
#include "Tools/circleselect.h"
#include "Tools/lassoselect.h"



ToolLibrary::ToolLibrary(UI* ui)
{
    this->ui = ui;

    setMinimumSize(200,50);
    setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setAlignment(Qt::AlignmentFlag::AlignLeft);
<<<<<<< Updated upstream
=======
#include "Tools/tool.h"
#include "Framework/toolpreset.h"
#include "Framework/toolmenu.h"
#include "Framework/toolmenuviewer.h"
#include "Ui/ui.h"

#include "Tools/pen.h"
#include "Tools/fill.h"
#include "Tools/eraser.h"
#include "Tools/selectionbox.h"
#include "Tools/circleselect.h"
#include "Tools/lassoselect.h"



ToolLibrary::ToolLibrary(UI* ui)
{
    this->ui = ui;

    setMinimumSize(200,50);
    setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setAlignment(Qt::AlignmentFlag::AlignLeft);
=======
>>>>>>> Stashed changes

    for(int i = 0; i < 5; i ++){
        Pen *pen = new Pen(ui);
        QColor color;
        color.setHsv(i*36,255,255);
        pen->setColor(color);
        pen->setWidth(i*2+4);
        addTool(pen);
    }
    for(int i = 0; i < 4; i ++){
        Fill *fill = new Fill(ui);
        QColor color;
        color.setHsv(i*36,255,255);
        fill->setColor(color);
        addTool(fill);
    }
    addTool(new Eraser(ui));
    SelectionBox* box = new SelectionBox(ui);
    addTool(box);
    addTool(new CircleSelect(ui, box));
    addTool(new LassoSelect(ui, box));
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}


void ToolLibrary::addTool(Tool *tool)
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    layout->addWidget(tool->toolPreset());
=======
    tools.append(tool);
    layout->addWidget(tool->toolPreset());
    active_tool = tool;
>>>>>>> Stashed changes
=======
    tools.append(tool);
    layout->addWidget(tool->toolPreset());
    active_tool = tool;
>>>>>>> Stashed changes
}


void ToolLibrary::setActiveTool(Tool *tool)
{
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    active_preset = tool;
=======
=======
>>>>>>> Stashed changes
    if(active_tool != nullptr){
        active_tool->deactivate();
    }

    ui->getToolMenuViewer()->setToolMenu(tool->getToolMenu());
    tool->activate();

    //why is this here
    foreach(Tool* tool, tools){
        tool->toolPreset()->update();
    }

    active_tool = tool;
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}
